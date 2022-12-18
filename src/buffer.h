#ifndef TED_BUFFER_H
#define TED_BUFFER_H

typedef struct {
	char *buf;
	int len;
} Buffer;

Buffer Buffer_init(void);
void Buffer_append(Buffer *, const char *, int);
void Buffer_reset(Buffer *);

#endif // TED_BUFFER_H
