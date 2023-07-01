/**
 * @file buffer.h
 * @brief Implementation of dynamic memory buffer.
 * @author thelissimus
 */

#pragma once

#include <stddef.h>

/**
 * @brief Dynamic memory buffer.
 * @remarks Not null terminated.
 * @since 0.1
 * @todo Implement more efficient generic buffer.
 */
struct buffer {
	/** @brief Memory buffer */
	void *buf;
	/** @brief Memory buffer length */
	size_t len;
};

/**
 * @brief Initializes an empty buffer.
 * @since 0.1
 *
 * @return Initialized buffer
 */
struct buffer buffer_init(void);

/**
 * @brief Frees memory used by the buffer and resets it to its initial value.
 * @since 0.1
 *
 * @param[out] buf Buffer to be reset
 */
void buffer_reset(struct buffer *buf);

/**
 * @brief Copies and appends @p n bytes of @p src into the @p buf.
 * @pre @p buf must be previously initialized.
 * @since 0.1
 *
 * @param[in,out] buf Buffer to be appended to
 * @param[in] src Source to be appended from
 * @param[in] n Number of bytes to copy from source
 */
void buffer_append(struct buffer *buf, const void *src, size_t n);
