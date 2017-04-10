#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma pack(push, 4)
struct mem_ctrl_t
{
	struct mem_ctrl_t *next;
	uint16_t          size;
    bool              status;
//	uint8_t           user_data[];
};
#pragma pack(pop)

struct mem_ctrl_t *MemCtrlBlock = NULL;

#pragma pack(push, 4)
uint8_t memory_buffer[1024];
#pragma pack(pop)

void mem_init(struct mem_ctrl_t **mem, uint8_t *buffer, uint16_t size)
{
	if (mem == NULL || buffer == NULL || size < sizeof(struct mem_ctrl_t))
	{
		return;
	}

	(*mem) = (struct mem_ctrl_t *)buffer;
    (*mem)->next   = NULL;
	(*mem)->size   = size - sizeof(struct mem_ctrl_t);
    (*mem)->status = false;
}

void mem_deinit(struct mem_ctrl_t **mem)
{
	(*mem) = NULL;
}

static inline
uint16_t mem_cal_alignment(uint16_t size, uint16_t alignment)
{
	uint16_t temp = size % alignment;
	uint16_t value = size;

	if (temp)
	{
		value += alignment - temp;
	}

	return value;
}

void *mem_malloc(struct mem_ctrl_t *mem, uint16_t size)
{
    struct mem_ctrl_t *now     = mem;
    struct mem_ctrl_t *next    = mem;
	uint16_t          freeSize = 0;
	uint16_t          useSize  = mem_cal_alignment(size, 4) + sizeof(struct mem_ctrl_t);

    if(mem == NULL || size == 0)
    {
        return NULL;
    }

    while(1)
    {
        if(now == NULL)
        {
            return NULL;
        }
        
        if(now->status == false)
        {
            if( now->size >= useSize )
            {
				freeSize     = now->size;
				now->size    = useSize;
                next         = (struct mem_ctrl_t *)((uint8_t *)now + useSize);
				next->size   = freeSize - useSize;

                next->next   = now->next;
                now->next    = next;
                
                next->status = false;
                now->status  = true;
                
                return (void *)(now+1);
            }
        }
        
        now = now->next;
    }
    
//    return NULL;
}

void mem_free(struct mem_ctrl_t *mem, void *buffer)
{
    struct mem_ctrl_t *now       = mem;
    struct mem_ctrl_t *last      = NULL;
    struct mem_ctrl_t *data_addr = NULL;
    
    if(buffer == NULL || mem == NULL)
    {
        return;
    }
    
    while(1)
    {
        if(now == NULL)
        {
            return;
        }
        
        // free memory
        data_addr = now + 1;
        if( data_addr == buffer )
        {
            now->status = false;
        }

        // merge memory block
        if( now->status == false )
        {
            if( last == NULL )
            {
                last = now;
            }
            else if(now->next == NULL)
            {
                if(now->status == false)
                {
                    last->next = NULL;
                    last->size = (now - last) * sizeof(struct mem_ctrl_t) + now->size;
                }
                else
                {
                    last->next = now;
                    last->size = (now - last) * sizeof(struct mem_ctrl_t);
                }
                
                last->status = false;
                last = NULL;
            }
        }
        else
        {
            if( last != NULL )
            {
                last->next = now;
                last->size = (now - last) * sizeof(struct mem_ctrl_t);
                last->status = false;
                last = NULL;
            }
        }

        now = now->next;
    }
}

uint8_t AllocSize1 = 0;
uint8_t AllocSize2 = 0;
uint8_t *AllocMem1 = NULL;
uint8_t *AllocMem2 = NULL;

int main(void)
{
    mem_init(&MemCtrlBlock, memory_buffer, sizeof(memory_buffer));

    while(1)
    {
        mem_free(MemCtrlBlock, AllocMem1);
        AllocSize1 = rand();
        AllocMem1 = (uint8_t *)mem_malloc(MemCtrlBlock, AllocSize1);
        
        mem_free(MemCtrlBlock, AllocMem2);
        AllocSize2 = rand();
        AllocMem2 = (uint8_t *)mem_malloc(MemCtrlBlock, AllocSize2);
    }
}
