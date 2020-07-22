#ifndef _UTILS_H_
#define _UTILS_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
// typedef struct parser Parser;
#define UNUSED __attribute__ ((unused))
#define NOT_REACHED() fprintf(stderr, "NOT_REACHED: %s:%d In function %s()", __FILE__, __LINE__, __func__)
void *memManager(void *ptr, uint32_t newSize);
uint32_t ceilToPowerOf2(uint32_t v);
//内存分配
#define ALLOCATE(type) (type *)memManager(NULL, sizeof(type))
//额外分配
#define ALLOCATE_EXTRA(mainType, extraSize) (mainType *)memManager(NULL, sizeof(mainType) + extraSize)
//分配数组
#define ALLOCATE_ARRAY(type, count) (type *)memManager(NULL, sizeof(type) * count)
//释放数组
#define DEALLOCATE(ptr) memManager(ptr, 0)




typedef struct
{
    char *str;
    uint32_t length;
} String;

typedef struct
{
    uint32_t length; //除结束'\0'之外的字符个数
    char start[0];   //类似c99中的柔性数组
} CharValue;         //字符串缓冲区
//声明buffer类型
#define DECLARE_BUFFER_TYPE(type)                          \
    typedef struct                                         \
    {                                                      \
        /* 数据缓冲区 */                              \
        type *datas;                                       \
        /*缓冲区中已使用的元素个数*/           \
        uint32_t count;                                    \
        /*缓冲区容量用*/                             \
        uint32_t capacity;                                 \
    } type##Buffer;                                        \
    void type##BufferInit(type##Buffer *buf);              \
    void type##BufferFillWrite(                            \
        type##Buffer *buf, type data, uint32_t fillCount); \
    void type##BufferAdd(type##Buffer *buf, type data);    \
    void type##BufferClear(type##Buffer *buf);
//定义buffer方法
#define DEFINE_BUFFER_METHOD(type)                                \
    void type##BufferInit(type##Buffer *buf)                      \
    {                                                             \
        buf->datas = NULL;                                        \
        buf->count = buf->capacity = 0;                           \
    }                                                             \
                                                                  \
    void type##BufferFillWrite(                                   \
        type##Buffer *buf, type data, uint32_t fillCount)         \
    {                                                             \
        uint32_t newCounts = buf->count + fillCount;              \
        if (newCounts > buf->capacity)                            \
        {                                                         \
            size_t oldSize = buf->capacity * sizeof(type);        \
            buf->capacity = ceilToPowerOf2(newCounts);            \
            size_t newSize = buf->capacity * sizeof(type);        \
            buf->datas = (type *)memManager(buf->datas, newSize); \
        }                                                         \
        uint32_t cnt = 0;                                         \
        while (cnt < fillCount)                                   \
        {                                                         \
            buf->datas[buf->count++] = data;                      \
            cnt++;                                                \
        }                                                         \
    }                                                             \
                                                                  \
    void type##BufferAdd(type##Buffer *buf, type data)            \
    {                                                             \
        type##BufferFillWrite(buf, data, 1);                      \
    }                                                             \
                                                                  \
    void type##BufferClear(type##Buffer *buf)                     \
    {                                                             \
        size_t oldSize = buf->capacity * sizeof(buf->datas[0]);   \
        memManager(buf->datas, 0);                                \
        type##BufferInit(buf);                                    \
    }

DECLARE_BUFFER_TYPE(String)
#define SymbolTable StringBuffer
typedef uint8_t Byte;
typedef char Char;
typedef int Int;
DECLARE_BUFFER_TYPE(Int)
DECLARE_BUFFER_TYPE(Char)
DECLARE_BUFFER_TYPE(Byte)
//错误处理
typedef enum
{
    ERROR_IO,
    ERROR_MEM,
    ERROR_LEX,
    ERROR_COMPILE,
    ERROR_RUNTIME
} ErrorType;
void errorReport(void *parser,
                 ErrorType errorType, const char *fmt, ...);

void symbolTableClear(SymbolTable *buffer);

#define IO_ERROR(...) \
    errorReport(NULL, ERROR_IO, __VA_ARGS__)

#define MEM_ERROR(...) \
    errorReport(NULL, ERROR_MEM, __VA_ARGS__)

#define LEX_ERROR(parser, ...) \
    errorReport(parser, ERROR_LEX, __VA_ARGS__)

#define COMPILE_ERROR(parser, ...) \
    errorReport(parser, ERROR_COMPILE, __VA_ARGS__)

#define RUN_ERROR(...) \
    errorReport(NULL, ERROR_RUNTIME, __VA_ARGS__)

#define DEFAULT_BUfFER_SIZE 512
#endif