#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>

#include "fio.h"

int log_info(const char *format, ...)
{
	char buffer[1024];
	va_list args;
	size_t len;

	va_start(args, format);
	len = vsprintf(buffer, format, args);
	va_end(args);

	if (is_backend)
		return fio_server_text_output(buffer, len);
	else
		return fwrite(buffer, len, 1, f_out);
}

int log_err(const char *format, ...)
{
	char buffer[1024];
	va_list args;
	size_t len;

	va_start(args, format);
	len = vsprintf(buffer, format, args);
	va_end(args);

	if (is_backend)
		return fio_server_text_output(buffer, len);
	else
		return fwrite(buffer, len, 1, f_err);
}