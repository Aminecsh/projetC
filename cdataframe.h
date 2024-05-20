#ifndef MYLIBRARY_H
#define MYLIBRARY_H


#include "column.h"
#include "sort.h"
#include "list.h"

typedef struct CDataframe {
	list *columns;
} CDATAFRAME;


CDATAFRAME *create_empty_cdataframe();

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size);

void display_cdataframe(const CDATAFRAME *to_display);

int fill_cdataframe_user_input(CDATAFRAME *to_fill);

int fill_cdataframe_hardcode(CDATAFRAME *to_fill);

void display_some_columns(const CDATAFRAME *to_display, const unsigned int limit);

int add_line(const CDATAFRAME *to_add);

void replace_value(const CDATAFRAME *to_replace, const unsigned int col_index, const unsigned int line_index,
                   const void *value);

void display_column_names(const CDATAFRAME *to_display);

int count_value_equal(const CDATAFRAME *to_search, const void *value);

void remove_line(const CDATAFRAME *to_remove);

void add_column(CDATAFRAME *to_add, COLUMN *col);

int check_value(const CDATAFRAME *to_search, const void *value, ENUM_TYPE type);

void remove_column(CDATAFRAME *to_remove);

void display_some_lines(const CDATAFRAME *to_display, const unsigned int limit);

int get_cdataframe_cols_size(const CDATAFRAME *cdf);

void delete_cdataframe(CDATAFRAME **cdf);

void delete_column_by_name(CDATAFRAME *cdf, char *col_name);

CDATAFRAME *load_from_csv(char *file_name, ENUM_TYPE *dftype, int size);

void save_into_csv(CDATAFRAME *cdf, char *file_name);

#endif //MYLIBRARY_H
