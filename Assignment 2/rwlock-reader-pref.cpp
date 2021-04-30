#include "rwlock.h"

long int reader_count;
long int writer_count;

long int reader_loop;
long int writer_loop;

int rwlock_enabled=1;

void InitalizeReadWriteLock(struct read_write_lock * rw)
{
	rw->wait_writer_num = 0;
	rw->reading = 0;
	pthread_mutex_init(&rw->mutex, NULL);
	pthread_cond_init(&rw->readers, NULL);
	pthread_cond_init(&rw->writers, NULL);
  //	Write the code for initializing your read-write lock.
}

void ReaderLock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);
	while(rw->wait_writer_num != 0)
		pthread_cond_wait(&rw->readers, &rw->mutex);
	rw->reading++;
	pthread_mutex_unlock(&rw->mutex);
  //	Write the code for aquiring read-write lock by the reader.
}

void ReaderUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);
	rw->reading--;
	pthread_mutex_unlock(&rw->mutex);
	pthread_cond_signal(&rw->writers);
  //	Write the code for releasing read-write lock by the reader.
}

void WriterLock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);
	while(rw->reading !=0 || rw->wait_writer_num != 0)
		pthread_cond_wait(&rw->writers, &rw->mutex);
	rw->wait_writer_num++;
	pthread_mutex_unlock(&rw->mutex);
  //	Write the code for aquiring read-write lock by the writer.
}

void WriterUnlock(struct read_write_lock * rw)
{
	pthread_mutex_lock(&rw->mutex);
	rw->wait_writer_num--;
	pthread_mutex_unlock(&rw->mutex);
	pthread_cond_signal(&rw->writers);
	pthread_cond_signal(&rw->readers);
  //	Write the code for releasing read-write lock by the writer.
}
