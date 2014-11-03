extern bool EM_any_errors;

void EM_newline(void);

extern int EM_tok_pos;

void EM_error(int, string,...);
void EM_impossible(string,...);
void EM_reset(string filename);
