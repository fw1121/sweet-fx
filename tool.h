#ifndef TOOL_H
#define TOOL_H

typedef struct Tool {
  char* name;
  char* desc;
  int   (*runner)(int argc, char* argv[]);
}
Tool;

Tool* Tool_get(char* name);
int   Tool_count(void);

#ifndef TOOL_C
extern Tool tool[];
extern int ntool;
#endif


#endif
