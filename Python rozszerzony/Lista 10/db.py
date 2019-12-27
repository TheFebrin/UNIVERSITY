import sys
from datetime import datetime
import sqlalchemy as db
from sqlalchemy.orm import sessionmaker
from sqlalchemy.types import Integer, Text, String
from sqlalchemy import create_engine
from sqlalchemy import Column, Integer, String, Text, DateTime, Float, Boolean, PickleType
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()
class Movie(Base):
    __tablename__ = 'Movie'
    id = Column(Integer,
                primary_key=True)
    title = Column(String(100),
                    unique=False,
                    nullable=False)
    year = Column(Integer,
                   unique=False,
                   nullable=False)
    director = Column(String(100),
                   unique=False,
                   nullable=False)
    producer = Column(String(100),
                   unique=False,
                   nullable=False)
    added = Column(DateTime,
                    default=datetime.now())

    def __repr__(self):
        return f'<Title: {self.title}, Year: {self.year}>'


def query(**kwargs):
    engine = create_engine('sqlite:///movies.db', echo=False)
    Base.metadata.create_all(engine)
    Session = sessionmaker(bind=engine)
    session = Session()

    if kwargs['flag'] == '--all':
        print('All movies:')
        movies = session.query(Movie).all()
        for m in movies:
            print(f'<Title: {m.title}, Year: {m.year}, '
                  f'Director: {m.director}, Producer: {m.producer}>')
    elif kwargs['flag'] == '--add':
        new_movie = Movie(title=kwargs['title'],
                          year=kwargs['year'],
                          director=kwargs['director'],
                          producer=kwargs['producer']
                          )
        session.add(new_movie)
        session.commit()
        print('Added movie: ', new_movie)
    elif kwargs['flag'] == '--delete':
        movies = session.query(Movie)
        attrs=[Movie.title, Movie.year, Movie.director, Movie.producer]
        for i, p in enumerate(kwargs['params']):
            movies = movies.filter(attrs[i]==p)

        movies = movies.all()
        for i, m in enumerate(movies):
            print(f'{i + 1}. Deleted: {m}')
            session.delete(m)
        session.commit()
    elif kwargs['flag'] == '--find':
        movies = session.query(Movie)
        attrs=[Movie.title, Movie.year, Movie.director, Movie.producer]
        for i, p in enumerate(kwargs['params']):
            movies = movies.filter(attrs[i]==p)

        movies = movies.all()
        for i, m in enumerate(movies):
            print(f'{i + 1}. {m}')
    else:
        print('Wrong kwargs: ', kwargs)
        exit()

    session.close()


if __name__ == '__main__':
    if sys.argv[1] == '--add':
        query(flag='--add', title=sys.argv[2],
                            year=sys.argv[3],
                            director=sys.argv[4],
                            producer=sys.argv[5],
                            )
    elif sys.argv[1] == '--delete':
        query(flag='--delete', params=sys.argv[2:])
    elif sys.argv[1] == '--find':
        query(flag='--find', params=sys.argv[2:])
    elif sys.argv[1] == '--all':
        query(flag='--all')
    else:
        args = ' '.join(sys.argv[1:])
        print(f'Unknown option: {args}')
        print('Usage: python db.py [option]')
        print('[--add title year director producer]\t: NO SPACES BETWEEN TITLE AND NAMES')
        print('[--delete title year director producer]\t\t\t: some suffix of params can be missing')
        print('[--find criterion:name]\t\t\t: find movies satisfying criterion')
        print('[--all]\t\t\t\t\t: print whole database')
