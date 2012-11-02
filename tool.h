#ifndef TOOL_H
#define TOOL_H

typedef struct Tool {
  char* name;
  char* desc;
  int   (*runner)(void);
  // options
}
Tool;

Tool* Tool_get(char* name);
int   Tool_count(void);
int   tool_run(Tool* tool);

#ifndef TOOL_C
extern Tool tool[];
extern int ntool;
#endif


#endif
