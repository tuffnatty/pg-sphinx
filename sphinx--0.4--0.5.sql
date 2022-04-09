DROP IF EXISTS FUNCTION sphinx_select;
DROP IF EXISTS FUNCTION sphinx_replace;
DROP IF EXISTS FUNCTION sphinx_delete;
DROP IF EXISTS TYPE sphinx_search_result;

CREATE TYPE sphinx_search_result AS (id bigint, weight int);

CREATE OR REPLACE FUNCTION sphinx_select(
  /*index*/     varchar,
  /*query*/     varchar,
  /*condition*/ varchar,
  /*order*/     varchar,
  /*offset*/    int,
  /*limit*/     int,
  /*options*/   varchar)
RETURNS SETOF sphinx_search_result
AS 'sphinx', 'pg_sphinx_select'
LANGUAGE C IMMUTABLE;

CREATE OR REPLACE FUNCTION sphinx_replace(
  /*index*/     varchar,
  /*id*/        bigint,
  /*data*/      varchar[])
RETURNS VOID
AS 'sphinx', 'pg_sphinx_replace'
LANGUAGE C IMMUTABLE;

CREATE OR REPLACE FUNCTION sphinx_delete(
  /*index*/     varchar,
  /*id*/        bigint)
RETURNS VOID
AS 'sphinx', 'pg_sphinx_delete'
LANGUAGE C IMMUTABLE;

