/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ring_buffer.h
*/

#ifndef RING_BUFFER_H_
# define RING_BUFFER_H_

typedef enum rn_type_u	rn_type_t;
typedef struct rb_s	rb_t;
typedef struct rn_s	rn_t;
typedef struct rb_it_s	rb_it_t;

enum rn_type_u
{
	UNUSED,
	USED,
	EXTRA
};

struct rn_s
{
	rn_type_t	type;
	struct rn_s	*next;
	struct rn_s	*prev;
	void		*data;
};

struct rb_s
{
	struct rn_s	*tail;
	struct rn_s	*head;
	struct rn_s	*buffers;
	size_t		max_buffers;
	size_t		nb_nodes;
};

struct rb_it_s
{
	rb_t	*buff;
	rn_t	*tmp;
};

/*	init.c		*/
int	rb_init(rb_t *ring, size_t max_buffers);
void	rn_init(rn_t *node);
void	rb_it_init(rb_it_t *it, rb_t *rb);

/*	deinit.c	*/
void	rb_deinit(rb_t *ring, bool free_self, bool free_data);
void	rn_deinit(rn_t *node, bool free_self, bool free_data);
void	rb_it_deinit(rb_it_t *it);

/*	rb_it.c		*/
void	rb_it_iterate(rb_it_t *it);
void	rb_it_erase(rb_it_t *it, bool free_data);
void	*rb_it_get(rb_it_t *it);
void	rb_it_set(rb_it_t *it, void *data);

/*	rb.c		*/
void	*rb_pop(rb_t *ring);
void	rb_clear(rb_t *ring, bool free_data);
size_t	rb_size(rb_t *ring);

/*	rb_push.c	*/
int	rb_push(rb_t *ring, void *data);
int	rb_push_front(rb_t *ring, void *data);

/*	rb_extract.c	*/
char	*extract_cmd_from_buff(rb_t *buff, const char *delims);
char	*rb_pop_head_no_delete(rb_t *buff);
void	*rb_pop_head(rb_t *ring);

#endif
