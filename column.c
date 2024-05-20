#include "column.h"
#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

COLUMN *create_column(const ENUM_TYPE type, char *title) {
	COLUMN *to_return = malloc(sizeof(COLUMN));
	if (to_return == NULL)
		return NULL;
	to_return->title = title;
	to_return->logical_size = 0;
	to_return->physical_size = 0;
	to_return->column_type = type;
	to_return->data = NULL;
	to_return->index = NULL;
	to_return->valid_index = 0;
	to_return->sort_dir = ASC;
	return to_return;
}

int insert_value(COLUMN *col, const void *value) {
	if (col == NULL)
		return 0;
	if (col->valid_index == 1)
		col->valid_index = -1;
	if (col->physical_size == 0) {
		col->index = malloc(sizeof(int) * REALOC_SIZE);
		if (col->index == NULL)
			return 0;
	} else if (col->logical_size == col->physical_size) {
		col->index = realloc(col->index, sizeof(int) * (col->physical_size + REALOC_SIZE));
		if (col->index == NULL)
			return 0;
	}
	col->index[col->logical_size] = col->logical_size;
	switch (col->column_type) {
		case UINT:
			if (col->physical_size == 0) {
				col->data = malloc(sizeof(unsigned int *) * REALOC_SIZE);
				if (col->data == NULL)
					return 0;
				col->physical_size = REALOC_SIZE;
			} else if (col->logical_size == col->physical_size) {
				col->data = realloc(col->data, sizeof(unsigned int *) * (col->physical_size + REALOC_SIZE));
				if (col->data == NULL)
					return 0;
				col->physical_size += REALOC_SIZE;
			}
			if (value == NULL) {
				col->data[col->logical_size] = NULL;
				break;
			}
			col->data[col->logical_size] = malloc(sizeof(unsigned int));
			if (col->data[col->logical_size] == NULL)
				return 0;
			*(unsigned int *) col->data[col->logical_size] = *(unsigned int *) value;
			break;
		case INT:
			if (col->physical_size == 0) {
				col->data = malloc(sizeof(int *) * REALOC_SIZE);
				if (col->data == NULL)
					return 0;
				col->physical_size = REALOC_SIZE;
			} else if (col->logical_size == col->physical_size) {
				col->data = realloc(col->data, sizeof(int *) * (col->physical_size + REALOC_SIZE));
				if (col->data == NULL)
					return 0;
				col->physical_size += REALOC_SIZE;
			}
			if (value == NULL) {
				col->data[col->logical_size] = NULL;
				break;
			}
			col->data[col->logical_size] = malloc(sizeof(int));
			if (col->data[col->logical_size] == NULL)
				return 0;
			*(int *) col->data[col->logical_size] = *(int *) value;
			break;
		case CHAR:
			if (col->physical_size == 0) {
				col->data = malloc(sizeof(char *) * REALOC_SIZE);
				if (col->data == NULL)
					return 0;
				col->physical_size = REALOC_SIZE;
			} else if (col->logical_size == col->physical_size) {
				col->data = realloc(col->data, sizeof(char *) * (col->physical_size + REALOC_SIZE));
				if (col->data == NULL)
					return 0;
				col->physical_size += REALOC_SIZE;
			}
			if (value == NULL) {
				col->data[col->logical_size] = NULL;
				break;
			}
			col->data[col->logical_size] = malloc(sizeof(char));
			if (col->data[col->logical_size] == NULL)
				return 0;
			*(char *) col->data[col->logical_size] = *(char *) value;
			break;
		case FLOAT:
			if (col->physical_size == 0) {
				col->data = malloc(sizeof(float *) * REALOC_SIZE);
				if (col->data == NULL)
					return 0;
				col->physical_size = REALOC_SIZE;
			} else if (col->logical_size == col->physical_size) {
				col->data = realloc(col->data, sizeof(float *) * (col->physical_size + REALOC_SIZE));
				if (col->data == NULL)
					return 0;
				col->physical_size += REALOC_SIZE;
			}
			if (value == NULL) {
				col->data[col->logical_size] = NULL;
				break;
			}
			col->data[col->logical_size] = malloc(sizeof(float));
			if (col->data[col->logical_size] == NULL)
				return 0;
			*(float *) col->data[col->logical_size] = *(float *) value;
			break;
		case DOUBLE:
			if (col->physical_size == 0) {
				col->data = malloc(sizeof(double *) * REALOC_SIZE);
				if (col->data == NULL)
					return 0;
				col->physical_size = REALOC_SIZE;
			} else if (col->logical_size == col->physical_size) {
				col->data = realloc(col->data, sizeof(double *) * (col->physical_size + REALOC_SIZE));
				if (col->data == NULL)
					return 0;
				col->physical_size += REALOC_SIZE;
			}
			if (value == NULL) {
				col->data[col->logical_size] = NULL;
				break;
			}
			col->data[col->logical_size] = malloc(sizeof(double));
			if (col->data[col->logical_size] == NULL)
				return 0;
			*(double *) col->data[col->logical_size] = *(double *) value;
			break;
		case STRING:
			if (col->physical_size == 0) {
				col->data = malloc(sizeof(char *) * REALOC_SIZE);
				if (col->data == NULL)
					return 0;
				col->physical_size = REALOC_SIZE;
			} else if (col->logical_size == col->physical_size) {
				col->data = realloc(col->data, sizeof(char *) * (col->physical_size + REALOC_SIZE));
				if (col->data == NULL)
					return 0;
				col->physical_size += REALOC_SIZE;
			}
			if (value == NULL) {
				col->data[col->logical_size] = NULL;
			} else {
				col->data[col->logical_size] = malloc(sizeof(char) * (strlen(value) + 1));
				if (col->data[col->logical_size] == NULL)
					return 0;
				strcpy(col->data[col->logical_size], value);
			}
			break;
		//maybe todo : STRUCT
		default:
			break;
	}
	col->logical_size += 1;
	return 1;
}

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size) {
	if (col->data[i] == NULL)
		return;
	switch (col->column_type) {
		case UINT:
			snprintf(str, size, "%u", *(unsigned int*)col->data[i]);
			break;
		case INT:
			snprintf(str, size, "%d", *(int*)col->data[i]);
			break;
		case CHAR:
			snprintf(str, size, "%c", *(char*)col->data[i]);
			break;
		case FLOAT:
			snprintf(str, size, "%f", *(float*)col->data[i]);
			break;
		case DOUBLE:
			snprintf(str, size, "%f", *(double*)col->data[i]);
		case STRING:
			snprintf(str, size, "%s", *(char**)col->data[i]);
			break;
		//todo : function to convert a struct into a string
		default:
			break;
	}
}

void delete_column(COLUMN **col) {
	for (int i = 0; i < (*col)->logical_size; i++)
		free((*col)->data[i]);
	free((*col)->data);
	free((*col)->index);
	free(*col);
}

void print_col(const COLUMN *col) {
	for (int i = 0; i < col->logical_size; i++) {
		if (col->data[i] == NULL)
			printf("[%d] NULL\n", i);
		else {
			switch (col->column_type) {
				case UINT:
					printf("[%d] %u\n", i, *(unsigned int *) col->data[i]);
					break;
				case INT:
					printf("[%d] %d\n", i, *(int *) col->data[i]);
					break;
				case CHAR:
					printf("[%d] %c\n", i, *(char *) col->data[i]);
					break;
				case FLOAT:
					printf("[%d] %f\n", i, *(float *) col->data[i]);
					break;
				case DOUBLE:
					printf("[%d] %f\n", i, *(double *) col->data[i]);
					break;
				case STRING:
					printf("[%d] %s\n", i, (char *) col->data[i]);
					break;
				//todo maybe : add structure
				default:
					break;
			}
		}
	}
}

int number_of_occurences(const COLUMN *col, const void *x) {
	int count = 0;
	for (int i = 0; i < col->logical_size; i++) {
		switch (col->column_type) {
			case UINT:
				if (*(unsigned int *) col->data[i] == *(unsigned int *) x)
					count++;
				break;
			case INT:
				if (*(int *) col->data[i] == *(int *) x)
					count++;
				break;
			case CHAR:
				if (*(char *) col->data[i] == *(char *) x)
					count++;
				break;
			case FLOAT:
				if (*(float *) col->data[i] == *(float *) x)
					count++;
				break;
			case DOUBLE:
				if (*(double *) col->data[i] == *(double *) x)
					count++;
				break;
			case STRING:
				if (strcmp((char *) col->data[i], (char *) x) == 0)
					count++;
				break;
			//maybe todo : struct
			default:
				break;
		}
	}
	return count;
}



int search_value_in_column(COLUMN *col, const void *val) {
	if (col->valid_index != 1)
		return -1;
	switch (col->column_type) {
		case UINT: {
			int low = 0;
			int high = col->logical_size - 1;
			unsigned int target = *(unsigned int *) val;

			while (low <= high) {
				int mid = low + (high - low) / 2;
				unsigned int mid_value = *(unsigned int *) col->data[col->index[mid]];

				if (mid_value < target) {
					low = mid + 1;
				} else if (mid_value > target) {
					high = mid - 1;
				} else {
					return 1;
				}
			}
			break;
		}
		case INT: {
			int low = 0;
			int high = col->logical_size - 1;
			int target = *(int *) val;

			while (low <= high) {
				int mid = low + (high - low) / 2;
				int mid_value = *(int *) col->data[col->index[mid]];

				if (mid_value < target) {
					low = mid + 1;
				} else if (mid_value > target) {
					high = mid - 1;
				} else {
					return 1;
				}
			}
			break;
		}
		case CHAR: {
			int low = 0;
			int high = col->logical_size - 1;
			char target = *(char *) val;

			while (low <= high) {
				int mid = low + (high - low) / 2;
				char mid_value = *(char *) col->data[col->index[mid]];

				if (mid_value < target) {
					low = mid + 1;
				} else if (mid_value > target) {
					high = mid - 1;
				} else {
					return 1;
				}
			}
			break;
		}
		case FLOAT: {
			int low = 0;
			int high = col->logical_size - 1;
			float target = *(float *) val;

			while (low <= high) {
				int mid = low + (high - low) / 2;
				float mid_value = *(float *) col->data[col->index[mid]];

				if (mid_value < target) {
					low = mid + 1;
				} else if (mid_value > target) {
					high = mid - 1;
				} else {
					return 1;
				}
			}
			break;
		}
		case DOUBLE: {
			int low = 0;
			int high = col->logical_size - 1;
			double target = *(double *) val;

			while (low <= high) {
				int mid = low + (high - low) / 2;
				double mid_value = *(double *) col->data[col->index[mid]];

				if (mid_value < target) {
					low = mid + 1;
				} else if (mid_value > target) {
					high = mid - 1;
				} else {
					return 1;
				}
			}
			break;
		}
		case STRING: {
			int low = 0;
			int high = col->logical_size - 1;
			char *target = (char *) val;

			while (low <= high) {
				int mid = low + (high - low) / 2;
				char *mid_value = (char *) (col->data[col->index[mid]]);

				int cmp_result = strcmp(mid_value, target);
				if (cmp_result < 0) {
					low = mid + 1;
				} else if (cmp_result > 0) {
					high = mid - 1;
				} else {
					return 1;
				}
			}
			break;
		}
		default:
			break;
	}
	return 0;
}
