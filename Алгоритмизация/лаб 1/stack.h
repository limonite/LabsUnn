void push(char* stack, int* top, char value);
char pop(char* stack, int* top);
char peek(char* stack, int top);
int is_empty(int top);
int is_full(int top);
void clear(int* top);

void fpush(float* stack, int* top, float value);
float fpop(float* stack, int* top);
float fpeek(float* stack, int top);