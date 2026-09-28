// Exercises the full range of literal syntax the lexer supports.

int decimal = 42;
int hex = 0x1F;
int octal = 012;
int binary = 0b1010;

unsigned int u_suffix = 42u;
long l_suffix = 42l;
long long ll_suffix = 42ll;
unsigned long long ull_suffix = 42ull;

float pi = 3.14f;
double e = 2.71828;
double tiny = 0.5;

char letter = 'a';
char newline = '\n';
char quote = '\'';

const char* greeting = "hello, world!";
const char* escaped = "quote: \" backslash: \\";

/* multi
   line
   comment */
int after_block_comment = 1;
