#include <stdio.h>
#include <stdlib.h>

#include "cdataframe.h"

int main(void) {
	ENUM_TYPE cdftype[] = {INT, CHAR, INT, INT};
	CDATAFRAME *dataframe1 = create_cdataframe(cdftype, 4);
	if (dataframe1 == NULL)
		return 1;

	COLUMN *col = create_column(STRING, "coucou");
	if (col == NULL)
		return 1;

	add_column(dataframe1, col);
	add_line(dataframe1);
	add_line(dataframe1);
	remove_line(dataframe1);
	display_some_lines(dataframe1, 1);
	char test = 'l';
	replace_value(dataframe1, 1, 0, &test);
	update_index(col);
	printf("check value : %d\n", check_value(dataframe1, "test", STRING));
	display_some_columns(dataframe1, 5);
	display_column_names(dataframe1);
	printf("nombre de valeurs égales : %d\n", count_value_equal(dataframe1, &test));

	display_cdataframe(dataframe1);
	delete_cdataframe(&dataframe1);

	//TESTS CSV
	ENUM_TYPE csv_types[] = {INT, STRING, DOUBLE};
	CDATAFRAME *test_csv = load_from_csv("test.csv", csv_types, 3);
	if (test_csv == NULL)
		return 1;
	display_some_lines(test_csv, 10);
	save_into_csv(test_csv, "fichier");

	delete_cdataframe(&test_csv);
	return 0;
}
