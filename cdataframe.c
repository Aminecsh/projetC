#include "cdataframe.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//Création d'un cdataframe vide
CDATAFRAME *create_empty_cdataframe() {
	CDATAFRAME *to_return = malloc(sizeof(CDATAFRAME));
	if (to_return == NULL)
		return NULL;
	to_return->columns = lst_create_list();
	if (to_return->columns == NULL)
		return NULL;
	return to_return;
}

/**
 * Création d'un dataframe
*/
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size) {
	CDATAFRAME *to_return = malloc(sizeof(CDATAFRAME));
	if (to_return == NULL)
		return NULL;
	to_return->columns = lst_create_list();
	if (to_return->columns == NULL)
		return NULL;
	for (int i = 0; i < size; i++) {
		COLUMN *c = create_column(cdftype[i], "hello");
		if (c == NULL)
			return NULL;
		lnode *to_insert = lst_create_lnode(c);
		if (to_insert == NULL)
			return NULL;
		lst_insert_tail(to_return->columns, to_insert);
	}
	return to_return;
}

/**
* @brief: Column deletion
* param1: Pointer to the CDataframe to delete */
void delete_cdataframe(CDATAFRAME **cdf) {
	lnode *curr = (*cdf)->columns->head;
	while (curr != NULL) {
		delete_column(&curr->data);
		curr = curr->next;
	}
	lst_delete_list((*cdf)->columns);
	free(*cdf);
	*cdf = NULL;
}

/**
 * @brief: Delete column by name
 * @param1: Pointer to the CDataframe
 * @param2: Column name
 */

void delete_column_by_name(CDATAFRAME *cdf, char *col_name) {
	lnode *curr = cdf->columns->head;
	while (curr != NULL) {
		if (strcmp(curr->data->title, col_name) == 0) {
			delete_column(&curr->data);
			lst_delete_lnode(cdf->columns, curr);
			break;
		}
		curr = curr->next;
	}
}

/**
 * @brief: Number of columns
 * @param1: Point to the CDataframe
 * @return: Number of columns in the CDataframe
 */
int get_cdataframe_cols_size(const CDATAFRAME *cdf) {
	int count = 0;
	lnode *curr = cdf->columns->head;
	while (curr != NULL) {
		count++;
		curr = curr->next;
	}
	return count;
}


//Remplissage du CDataframe à partir de saisies utilisateurs
int fill_cdataframe_user_input(CDATAFRAME *to_fill) {
	int number_of_columns;
	printf("Saisissez le nombre de colonnes voulues\n");
	scanf("%d", &number_of_columns);


	for (int i = 0; i < number_of_columns; i++) {
		COLUMN *c = create_column(INT, "hello");
		if (c == NULL)
			return 0;
		lnode *to_insert = lst_create_lnode(c);
		if (to_insert == NULL)
			return 0;
		lst_insert_tail(to_fill->columns, to_insert);
	}
	return 1;
}

//Remplissage en dur du CDataframe
int fill_cdataframe_hardcode(CDATAFRAME *to_fill) {
	int number_of_columns = 5;

	for (int i = 0; i < number_of_columns; i++) {
		COLUMN *c = create_column(INT, "hello");
		if (c == NULL)
			return 0;
		lnode *to_insert = lst_create_lnode(c);
		if (to_insert == NULL)
			return 0;
		lst_insert_tail(to_fill->columns, to_insert);
	}
	return 1;
}


//Afficher tout le CDataframe
void display_cdataframe(const CDATAFRAME *to_display) {
	int i = 0;
	lnode *curr = to_display->columns->head;
	while (curr != NULL) {
		printf("titre colonne %d: %s\n", i, curr->data->title);
		printf("taille logique colonne %d: %d\n", i, curr->data->logical_size);
		printf("taille physique colonne %d: %d\n", i, curr->data->physical_size);
		printf("Tableau colonne %d : ", i);
		print_col(curr->data);
		curr = curr->next;
		i++;
		printf("\n");
	}
}


//Afficher une partie des lignes du CDataframe selon une limite fournie par l'utilisateur
void display_some_lines(const CDATAFRAME *to_display, const unsigned int limit) {
	unsigned int i = 0;
	while (i < limit) {
		lnode *curr = to_display->columns->head;
		printf("Ligne %d : \n", i);
		while (curr != NULL && i < limit) {
			if (curr->data->data[i] != NULL) {
				switch (curr->data->column_type) {
					case UINT:
						printf("%u ", *(unsigned int *) curr->data->data[i]);
						break;
					case INT:
						printf("%d ", *(int *) curr->data->data[i]);
						break;
					case CHAR:
						printf("%c ", *(char *) curr->data->data[i]);
						break;
					case FLOAT:
						printf("%f ", *(float *) curr->data->data[i]);
						break;
					case DOUBLE:
						printf("%f ", *(double *) curr->data->data[i]);
						break;
					case STRING:
						printf("%s ", (char *) curr->data->data[i]);
						break;
					//todo maybe : add struct
					default:
						break;
				}
			} else {
				printf("NULL ");
			}
			curr = curr->next;
		}
		printf("\n");
		i++;
	}
}


//Afficher une partie des colonnes du CDataframe selon une limite fournie par l'utilisateur
void display_some_columns(const CDATAFRAME *to_display, const unsigned int limit) {
	lnode *curr = to_display->columns->head;
	int i = 0;
	while (curr != NULL) {
		printf("titre colonne %d: %s\n", i, curr->data->title);
		printf("taille logique colonne %d: %d\n", i, curr->data->logical_size);
		printf("taille physique colonne %d: %d\n", i, curr->data->physical_size);
		printf("Tableau colonne %d : ", i);
		print_col(curr->data);
		printf("\n");
		curr = curr->next;
		i++;
	}
}


//Ajouter une ligne de valeurs au CDataframe
int add_line(const CDATAFRAME *to_add) {
	lnode *curr = to_add->columns->head;
	int i = 0;
	while (curr != NULL) {
		switch (curr->data->column_type) {
			case UINT: {
				unsigned int a = 3;
				if (insert_value(curr->data, &a) != 1)
					return 0;
				break;
			}
			case INT: {
				int b = 4;
				if (insert_value(curr->data, &b) != 1)
					return 0;
				break;
			}
			case CHAR: {
				char c = 'v';
				if (insert_value(curr->data, &c) != 1)
					return 0;
				break;
			}
			case FLOAT: {
				float d = 4.2;
				if (insert_value(curr->data, &d) != 1)
					return 0;
				break;
			}
			case DOUBLE: {
				double e = 5.342;
				if (insert_value(curr->data, &e) != 1)
					return 0;
				break;
			}
			case STRING:
				if (insert_value(curr->data, "test") != 1)
					return 0;
				break;
			default:
				break;
		}
		curr = curr->next;
		i++;
	}
	return 1;
}


//Supprimer une ligne de valeurs du CDataframe
void remove_line(const CDATAFRAME *to_remove) {
	lnode *curr = to_remove->columns->head;
	while (curr != NULL) {
		if (curr->data->logical_size != 0) {
			free(curr->data->data[curr->data->logical_size - 1]);
			curr->data->data[curr->data->logical_size - 1] = NULL;
			curr->data->logical_size -= 1;
		}
		curr = curr->next;
	}
}


//Ajouter une colonne au CDataframe
void add_column(CDATAFRAME *to_add, COLUMN *col) {
	lnode *node = lst_create_lnode(col);
	lst_insert_tail(to_add->columns, node);
}


//Supprimer une colonne du CDataframe
void remove_column(CDATAFRAME *to_remove) {
	lst_delete_tail(to_remove->columns);
}


//Renommer le titre d'une colonne du CDataframe
void rename_title(const CDATAFRAME *to_rename, const int index, char *new_title) {
	lnode *curr = to_rename->columns->head;
	int i = 0;
	while (curr != NULL) {
		if (i == index)
			curr->data->title = new_title;
		curr = curr->next;
		i++;
	}
}


//Vérifier l'existence d'une valeur dans le CDataframe (retourne 1 si trouvé, 0 sinon)
int check_value(const CDATAFRAME *to_search, const void *value, ENUM_TYPE type) {
	lnode *curr = to_search->columns->head;
	while (curr != NULL) {
		if (type == curr->data->column_type) {
			if (search_value_in_column(curr->data, value) == 1)
				return 1;
		}
		curr = curr->next;
	}
	return 0;
}


//Accéder/remplacer la valeur se trouvant dans une cellule du CDataframe en utilisant son numéro de ligne et de colonne
void replace_value(const CDATAFRAME *to_replace, const unsigned int col_index, const unsigned int line_index,
                   const void *value) {
	lnode *curr = to_replace->columns->head;
	int i = 0;
	while (curr != NULL) {
		if (i == col_index) {
			switch (curr->data->column_type) {
				case UINT:
					*(unsigned int *) curr->data->data[line_index] = *(unsigned int *) value;
				case INT:
					*(int *) curr->data->data[line_index] = *(int *) value;
					break;
				case CHAR:
					*(char *) curr->data->data[line_index] = *(char *) value;
					break;
				case FLOAT:
					*(float *) curr->data->data[line_index] = *(float *) value;
					break;
				case DOUBLE:
					*(double *) curr->data->data[line_index] = *(double *) value;
					break;
				case STRING:
					curr->data->data[line_index] = (COL_TYPE *) value;
					break;
				//todo maybe : struct
				default:
					break;
			}
		}
		curr = curr->next;
		i++;
	}
}


//Afficher les noms des colonnes
void display_column_names(const CDATAFRAME *to_display) {
	lnode *curr = to_display->columns->head;
	while (curr != NULL) {
		printf("Nom colonne : %s\n", curr->data->title);
		curr = curr->next;
	}
}


//Afficher le nombre de lignes
void display_line_count(const CDATAFRAME *to_display) {
	printf("Le nombre de lignes est de %d\n", to_display->columns->head->data->logical_size);
}


//Afficher le nombre de colonnes
void display_column_count(const CDATAFRAME *to_display) {
	printf("Le nombre de colonnes est de %d\n", get_cdataframe_cols_size(to_display));
}


//Nombre de cellules contenant une valeur égale à x (x donné en paramètre)
int count_value_equal(const CDATAFRAME *to_search, const void *value) {
	int count = 0;
	lnode *curr = to_search->columns->head;
	while (curr != NULL) {
		count += number_of_occurences(curr->data, value);
		curr = curr->next;
	}
	return count;
}


//Nombre de cellules contenant une valeur supérieure à x (x donné en paramètre)
int count_value_superior(const CDATAFRAME *to_search, const int value) {
	int count = 0;
	lnode *curr = to_search->columns->head;
	while (curr != NULL) {
		count += number_of_higher_occurences(curr->data, value);
		curr = curr->next;
	}
	return count;
}

//Nombre de cellules contenant une valeur inférieure à x (x donné en paramètre)
int count_value_inferior(const CDATAFRAME *to_search, const int value) {
	int count = 0;
	lnode *curr = to_search->columns->head;
	while (curr != NULL) {
		count += number_of_lower_occurences(curr->data, value);
		curr = curr->next;
	}
	return count;
}

/**
* @brief: Create a CDataframe from csvfile
* @param1: CSV filename
* @param2: Array of types
* @param3: Size of array in param2
*/
CDATAFRAME *load_from_csv(char *file_name, ENUM_TYPE *dftype, int size) {
	char ligne[81];
	unsigned int parsed_uint;
	int parsed_integer;
	float parsed_float;
	char parsed_char;
	char parsed_string[100];
	double parsed_double;
	char *temp_string;
	CDATAFRAME *to_return = create_cdataframe(dftype, size);
	if (to_return == NULL)
		return NULL;
	FILE *fic = fopen(file_name, "rt");
	if (fic == NULL) {
		delete_cdataframe(&to_return);
		return NULL;
	}
	for (int i = 0; fgets(ligne, 81, fic) != NULL; i++) {
		temp_string = strtok(ligne, ",");
		lnode *curr = to_return->columns->head;
		for (int col = 0; col < size && temp_string != NULL; col++) {
			switch (dftype[col]) {
				case UINT:
					if (sscanf(temp_string, "%u", &parsed_uint) != 1)
						return NULL;
					insert_value(curr->data, &parsed_uint);
					break;
				case INT:
					if (sscanf(temp_string, "%d", &parsed_integer) != 1)
						return NULL;
					insert_value(curr->data, &parsed_integer);
					break;
				case CHAR:
					if (sscanf(temp_string, "%c", &parsed_char) != 1)
						return NULL;
					insert_value(curr->data, &parsed_char);
					break;
				case FLOAT:
					if (sscanf(temp_string, "%f", &parsed_float) != 1)
						return NULL;
					insert_value(curr->data, &parsed_float);
					break;
				case DOUBLE:
					if (sscanf(temp_string, "%lf", &parsed_double) != 1)
						return NULL;
					insert_value(curr->data, &parsed_double);
					break;
				case STRING:
					if (sscanf(temp_string, "%s", parsed_string) != 1)
						return NULL;
					insert_value(curr->data, parsed_string);
					break;
				default:
					break;
			}
			curr = curr->next;
			temp_string = strtok(NULL, ",");
		}
	}
	fclose(fic);
	return to_return;
}

/**
 * @brief: Export into a csvfile
 * @param1: Pointer to the CDataframe
 * @param2: csv filename where export file, if the file exists,
 *          it will be overwritten
 */
void save_into_csv(CDATAFRAME *cdf, char *file_name) {
	FILE *fd = fopen(file_name, "w+");
	if (fd == NULL)
		return;

	unsigned int i = 0;
	while (i < cdf->columns->head->data->logical_size) {
		lnode *curr = cdf->columns->head;
		int first = 1;
		while (curr != NULL && i < curr->data->logical_size) {
			if (!first) {
				fprintf(fd, ",");
			}
			first = 0;
			if (curr->data->data[i] != NULL) {
				switch (curr->data->column_type) {
					case UINT:
						fprintf(fd, "%u", *(unsigned int *) curr->data->data[i]);
						break;
					case INT:
						fprintf(fd, "%d", *(int *) curr->data->data[i]);
						break;
					case CHAR:
						fprintf(fd, "%c", *(char *) curr->data->data[i]);
						break;
					case FLOAT:
						fprintf(fd, "%f", *(float *) curr->data->data[i]);
						break;
					case DOUBLE:
						fprintf(fd, "%f", *(double *) curr->data->data[i]);
						break;
					case STRING:
						fprintf(fd, "%s", (char *) curr->data->data[i]);
						break;
					//todo maybe : add struct
					default:
						break;
				}
			} else {
				fprintf(fd, "NULL,");
			}
			curr = curr->next;
		}
		fprintf(fd, "\n");
		i++;
	}
	fclose(fd);
}
