#include "sort.h"
#include <string.h>

int compareUint(const unsigned int *a, const unsigned int *b, int sort_dir) {
	unsigned int arg1 = *a;
	unsigned int arg2 = *b;
	if (sort_dir == 0)
		return (arg1 > arg2) - (arg1 < arg2);
	return (arg2 > arg1) - (arg2 < arg1);
}

int compareInt(const int *a, const int *b, int sort_dir) {
	int arg1 = *a;
	int arg2 = *b;
	if (sort_dir == 0)
		return (arg1 > arg2) - (arg1 < arg2);
	return (arg2 > arg1) - (arg2 < arg1);
}

int compareChar(const char *a, const char *b, int sort_dir) {
	char arg1 = *a;
	char arg2 = *b;
	if (sort_dir == 0)
		return (arg1 > arg2) - (arg1 < arg2);
	return (arg2 > arg1) - (arg2 < arg1);
}

int compareFloat(const float *a, const float *b, int sort_dir) {
	float arg1 = *a;
	float arg2 = *b;
	if (sort_dir == 0)
		return (arg1 > arg2) - (arg1 < arg2);
	return (arg2 > arg1) - (arg2 < arg1);
}

int compareDouble(const double *a, const double *b, int sort_dir) {
	double arg1 = *a;
	double arg2 = *b;
	if (sort_dir == 0)
		return (arg1 > arg2) - (arg1 < arg2);
	return (arg2 > arg1) - (arg2 < arg1);
}

int compareString(const char *a, const char *b, int sort_dir) {
	const char *arg1 = a;
	const char *arg2 = b;
	if (sort_dir == 0)
		return strcmp(arg1, arg2);
	return -strcmp(arg1, arg2);
}

int comp(void *first, void *second, int type, int sort_dir) {
	switch (type) {
		case UINT:
			return compareUint(first, second, sort_dir);
		case INT:
			return compareInt(first, second, sort_dir);
		case CHAR:
			return compareChar(first, second, sort_dir);
		case FLOAT:
			return compareFloat(first, second, sort_dir);
		case DOUBLE:
			return compareDouble(first, second, sort_dir);
		case STRING:
			return compareString(first, second, sort_dir);
		default:
			return -1;
	}
}

void swap(unsigned long long int *a, unsigned long long int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int Partition(COL_TYPE **data, int type, unsigned long long int *index, int left, int right, int sort_dir) {
	void *pivot = data[index[right]];
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (comp(data[index[j]], pivot, type, sort_dir) <= 0) {
			i++;
			swap(&index[i], &index[j]);
		}
	}
	swap(&index[i + 1], &index[left]);
	return i + 1;
}

void Quicksort(COL_TYPE **data, int type, unsigned long long int *index, int left, int right, int sort_dir) {
	if (left < right) {
		int pi = Partition(data, type, index, left, right, sort_dir);
		Quicksort(data, type, index, left, pi - 1, sort_dir);
		Quicksort(data, type, index, pi + 1, right, sort_dir);
	}
}


void sort(COLUMN *col, int sort_dir) {
	if (col->valid_index == -1) {
		switch (col->column_type) {
			case UINT:
				for (int i = 1; i < col->logical_size; i++) {
					int current_index = col->index[i];
					unsigned int current_value = *(unsigned int *) col->data[current_index];
					int j = i - 1;
					if (sort_dir == 0) {
						while (j >= 0 && *(unsigned int *) col->data[col->index[j]] > current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					} else if (sort_dir == 1) {
						while (j >= 0 && *(unsigned int *) col->data[col->index[j]] < current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					}
					col->index[j + 1] = current_index;
				}
				break;
			case INT:
				for (int i = 1; i < col->logical_size; i++) {
					int current_index = col->index[i];
					int current_value = *(int *) col->data[current_index];
					int j = i - 1;
					if (sort_dir == 0) {
						while (j >= 0 && *(int *) col->data[col->index[j]] > current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					} else if (sort_dir == 1) {
						while (j >= 0 && *(int *) col->data[col->index[j]] < current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					}
					col->index[j + 1] = current_index;
				}
				break;
			case CHAR:
				for (int i = 1; i < col->logical_size; i++) {
					int current_index = col->index[i];
					char current_value = *(char *) col->data[current_index];
					int j = i - 1;
					if (sort_dir == 0) {
						while (j >= 0 && *(char *) col->data[col->index[j]] > current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					} else if (sort_dir == 1) {
						while (j >= 0 && *(char *) col->data[col->index[j]] < current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					}
					col->index[j + 1] = current_index;
				}
				break;
			case FLOAT:
				for (int i = 1; i < col->logical_size; i++) {
					int current_index = col->index[i];
					float current_value = *(float *) col->data[current_index];
					int j = i - 1;
					if (sort_dir == 0) {
						while (j >= 0 && *(float *) col->data[col->index[j]] > current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					} else if (sort_dir == 1) {
						while (j >= 0 && *(float *) col->data[col->index[j]] < current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					}
					col->index[j + 1] = current_index;
				}
				break;
			case DOUBLE:
				for (int i = 1; i < col->logical_size; i++) {
					int current_index = col->index[i];
					double current_value = *(double *) col->data[current_index];
					int j = i - 1;
					if (sort_dir == 0) {
						while (j >= 0 && *(double *) col->data[col->index[j]] > current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					} else if (sort_dir == 1) {
						while (j >= 0 && *(double *) col->data[col->index[j]] < current_value) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					}
					col->index[j + 1] = current_index;
				}
				break;
			case STRING:
				for (int i = 1; i < col->logical_size; i++) {
					int current_index = col->index[i];
					char *current_value = *(char **) col->data[current_index];
					int j = i - 1;
					if (sort_dir == 0) {
						while (j >= 0 && strcmp(*(char **) col->data[col->index[j]], current_value) > 0) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					} else if (sort_dir == 1) {
						while (j >= 0 && strcmp(*(char **) col->data[col->index[j]], current_value) < 0) {
							col->index[j + 1] = col->index[j];
							j--;
						}
					}
					col->index[j + 1] = current_index;
				}
				break;
			//maybe todo : structs
			default:
				break;
		}
	} else if (col->valid_index == 0) {
		Quicksort(col->data, col->column_type, col->index, 0, col->logical_size - 1, sort_dir);
	}
	col->valid_index = 1;
}
