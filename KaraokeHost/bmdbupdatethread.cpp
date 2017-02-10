/*
 * Copyright (c) 2013-2017 Thomas Isaac Lightburn
 *
 *
 * This file is part of OpenKJ.
 *
 * OpenKJ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "bmdbupdatethread.h"
#include <QDir>
#include <QDirIterator>
#include <QSqlQuery>
#include <QFileInfo>
#include "tagreader.h"

BmDbUpdateThread::BmDbUpdateThread(QObject *parent) :
    QThread(parent)
{
}

QString BmDbUpdateThread::path() const
{
    return m_path;
}

void BmDbUpdateThread::setPath(const QString &path)
{
    m_path = path;
}

QStringList *BmDbUpdateThread::findMediaFiles(QString directory)
{
    QStringList *files = new QStringList();
    QDir dir(directory);
    QDirIterator iterator(dir.absolutePath(), QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        iterator.next();
        if (!iterator.fileInfo().isDir()) {
            QString filename = iterator.filePath();
            if (filename.endsWith(".mp3",Qt::CaseInsensitive) || filename.endsWith(".wav",Qt::CaseInsensitive) || filename.endsWith(".ogg",Qt::CaseInsensitive) || filename.endsWith(".flac",Qt::CaseInsensitive) || filename.endsWith(".m4a", Qt::CaseInsensitive))
            {
                files->append(filename);
            }
        }
    }
    return files;
}

void BmDbUpdateThread::run()
{
    TagReader reader;
    QStringList *files = findMediaFiles(m_path);
    QSqlQuery query;
    query.exec("BEGIN TRANSACTION");
    for (int i=0; i < files->size(); i++)
    {
        //TagReader reader;
        reader.setMedia(files->at(i).toLocal8Bit());
        QString duration = QString::number(reader.getDuration() / 1000);
        QString artist = reader.getArtist();
        QString title = reader.getTitle();
        QString filename = QFileInfo(files->at(i)).fileName();
        QString queryString = "INSERT OR IGNORE INTO songs (artist,title,path,filename,duration,searchstring) VALUES(\"" + artist + "\",\"" + title + "\",\"" + files->at(i) + "\",\"" + filename + "\",\"" + duration + "\",\"" + artist + title + filename + "\")";
        query.exec(queryString);
    }
    query.exec("COMMIT TRANSACTION");
    delete files;
}
