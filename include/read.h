#ifndef READ_H
#define READ_H

#ifndef READ_DATA_C
extern void read_head(t_head *head_file, FILE *in);
extern void read_Qcharge_conf(double *Q_charge, int *n_conf, t_head head_file, FILE *in);
extern void read_Qcharge(double **Q_charge, int n_conf, t_head head_file, FILE *in);
#endif

#ifndef READ_IN_C
extern void read_string(char *string, char *set, char *in_path);
extern void read_n_string(char **string, int dim, char *set, char *in_path);
extern void read_int(int *num, char *set, char *in_path);
extern void read_n_int(int *num, int dim, char *set, char *in_path);
extern void read_double(double *num, char *set, char *in_path);
extern void read_n_double(double *num, int dim, char *set, char *in_path);
#endif

#endif
