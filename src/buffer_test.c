#include <criterion/criterion.h>
#include <string.h>

#include "buffer.h"

#define MESSAGE(msg, fmt_want, fmt_got)                                        \
	"" msg "\n"                                                            \
	"want: '" fmt_want "'\n"                                               \
	"got: '" fmt_got "'"

Test(buffer, init)
{
	struct buffer buffer;

	buffer = buffer_init();

	cr_expect(buffer.buf == NULL,
		MESSAGE("initial content must be NULL", "%p", "%p"), NULL,
		buffer.buf);
	cr_expect(buffer.len == 0,
		MESSAGE("initial length must be '0'", "%d", "%zu"), 0,
		buffer.len);
}

Test(buffer, reset)
{
	struct buffer buffer;

	buffer.buf = malloc(10);
	buffer.len = 10;
	buffer_reset(&buffer);

	cr_expect(buffer.buf == NULL,
		MESSAGE("reset content must be NULL", "%p", "%p"), NULL,
		buffer.buf);
	cr_expect(buffer.len == 0,
		MESSAGE("reset length must be '0'", "%d", "%zu"), 0,
		buffer.len);
}

Test(buffer, append_char)
{
	struct buffer buffer;

	const char str[4] = { 'a', 'b', 'c', 'd' };
	buffer = buffer_init();
	buffer_append(&buffer, str, sizeof str);

	cr_expect(buffer.len == sizeof str,
		MESSAGE("appended length must be correct", "%zu", "%zu"),
		sizeof str, buffer.len);
	cr_expect(memcmp(buffer.buf, str, sizeof str) == 0,
		MESSAGE("appended content must be correct", "%s", "%s"), str,
		(char *) buffer.buf);
}

Test(buffer, append_char_multiple)
{
	struct buffer buffer;

	const char a[4] = { 'a', 'b', 'c', 'd' }, b[4] = { 'e', 'f', 'g', 'h' };
	const char want[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
	buffer = buffer_init();
	buffer_append(&buffer, a, sizeof a);
	buffer_append(&buffer, b, sizeof b);

	cr_expect(buffer.len == sizeof want,
		MESSAGE("appended length must be correct", "%zu", "%zu"),
		sizeof want, buffer.len);
	cr_expect(memcmp(buffer.buf, want, sizeof want) == 0,
		MESSAGE("appended content must be correct", "%s", "%s"), want,
		(char *) buffer.buf);
}

Test(buffer, append_num)
{
	struct buffer buffer;

	const int xs[4] = { 1, 2, 3, 4 };
	buffer = buffer_init();
	buffer_append(&buffer, xs, sizeof xs);

	cr_expect(buffer.len == sizeof xs,
		MESSAGE("appended length must be correct", "%zu", "%zu"),
		sizeof xs, buffer.len);
	cr_expect(memcmp(buffer.buf, xs, sizeof xs) == 0,
		"appended content must be correct");
}

Test(buffer, append_num_multiple)
{
	struct buffer buffer;

	const int a[4] = { 1, 2, 3, 4 }, b[4] = { 5, 6, 7, 8 };
	const int want[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	buffer = buffer_init();
	buffer_append(&buffer, a, sizeof a);
	buffer_append(&buffer, b, sizeof b);

	cr_expect(buffer.len == sizeof want,
		MESSAGE("appended length must be correct", "%zu", "%zu"),
		sizeof want, buffer.len);
	cr_expect(memcmp(buffer.buf, want, sizeof want) == 0,
		"appended content must be correct");
}
