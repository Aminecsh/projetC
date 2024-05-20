#ifndef COLUMN_H
#define COLUMN_H

#define REALOC_SIZE 256

enum enum_type {
	NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};

typedef enum enum_type ENUM_TYPE;

union column_type {
	unsigned int uint_value;
	signed int int_value;
	char char_value;
	float float_value;
	double double_value;
	char *string_value;
	void *struct_value;
};

typedef union column_type COL_TYPE;

typedef struct COLUMN {
	char *title;
	unsigned int physical_size;
	unsigned int logical_size;
	ENUM_TYPE column_type;
	COL_TYPE **data;
	unsigned long long int *index;
	int valid_index;
	int sort_dir;
	//int	*data;
} COLUMN;

COLUMN *create_column(const ENUM_TYPE type, char *title);

int insert_value(COLUMN *col, const void *value);

void print_col(const COLUMN *col);

void print_col_by_index(COLUMN *col);

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);

int number_of_occurences(const COLUMN *col, const void *x);

int number_of_higher_occurences(const COLUMN *col, const int x);

int number_of_lower_occurences(const COLUMN *col, const int x);

void update_index(COLUMN *col);

int search_value_in_column(COLUMN *col, const void *val);

void delete_column(COLUMN **col);

#endif //COLUMN_H
