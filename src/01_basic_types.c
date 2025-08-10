/*
 * ========================================
 * C语言完整教程 - 基础数据类型详解
 * 
 * 作者: zhiqiu314
 * 版本: v1.0.0
 * 创建时间: 2025-08-10
 * 更新时间: 2025-08-10
 * 
 * 本文件详细介绍了C语言的基础数据类型，包括：
 * 1. 整型数据类型及其变种
 * 2. 浮点型数据类型
 * 3. 字符型数据类型
 * 4. 布尔型数据类型
 * 5. 类型转换机制
 * 6. 输入输出格式化
 * 7. 底层存储原理
 * ========================================
 */

#define _CRT_SECURE_NO_WARNINGS  // Windows平台禁用安全警告
#include <stdio.h>      // 标准输入输出
#include <stdint.h>     // 固定宽度整型
#include <inttypes.h>   // 打印格式宏
#include <float.h>      // 浮点数限制
#include <math.h>       // 数学函数
#include <stdbool.h>    // 布尔类型
#include <limits.h>     // 整型限制
#include <string.h>     // 字符串函数
#include <stdlib.h>     // 标准库函数

/*
 * ========================================
 * 调试和辅助宏定义
 * ========================================
 */
#define DEBUG_PRINT(fmt, ...) \
    printf("[DEBUG] %s:%d " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define SECTION_HEADER(title) \
    printf("\n" "="*60 "\n%s\n" "="*60 "\n", title)

#define BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BINARY(byte) \
    (byte & 0x80 ? '1' : '0'), \
    (byte & 0x40 ? '1' : '0'), \
    (byte & 0x20 ? '1' : '0'), \
    (byte & 0x10 ? '1' : '0'), \
    (byte & 0x08 ? '1' : '0'), \
    (byte & 0x04 ? '1' : '0'), \
    (byte & 0x02 ? '1' : '0'), \
    (byte & 0x01 ? '1' : '0')

/*
 * ========================================
 * 1. 整型数据类型详解
 * ========================================
 */
void demonstrate_integer_types() {
    SECTION_HEADER("1. 整型数据类型详解");
    
    printf("=== 基本整型 ===\n");
    
    // char类型 - 通常为1字节
    char c = 'A';
    unsigned char uc = 255;
    signed char sc = -128;
    
    printf("char 'A': %c, ASCII: %d, 大小: %zu字节\n", c, c, sizeof(c));
    printf("unsigned char: %u, 大小: %zu字节, 范围: 0-%u\n", 
           uc, sizeof(uc), UCHAR_MAX);
    printf("signed char: %d, 大小: %zu字节, 范围: %d-%d\n", 
           sc, sizeof(sc), SCHAR_MIN, SCHAR_MAX);
    
    // short类型 - 通常为2字节
    short s = 32767;
    unsigned short us = 65535;
    
    printf("\nshort: %hd, 大小: %zu字节, 范围: %d-%d\n", 
           s, sizeof(s), SHRT_MIN, SHRT_MAX);
    printf("unsigned short: %hu, 大小: %zu字节, 范围: 0-%u\n", 
           us, sizeof(us), USHRT_MAX);
    
    // int类型 - 通常为4字节
    int i = 2147483647;
    unsigned int ui = 4294967295U;
    
    printf("\nint: %d, 大小: %zu字节, 范围: %d-%d\n", 
           i, sizeof(i), INT_MIN, INT_MAX);
    printf("unsigned int: %u, 大小: %zu字节, 范围: 0-%u\n", 
           ui, sizeof(ui), UINT_MAX);
    
    // long类型 - 32位系统通常4字节，64位系统可能8字节
    long l = 2147483647L;
    unsigned long ul = 4294967295UL;
    
    printf("\nlong: %ld, 大小: %zu字节, 范围: %ld-%ld\n", 
           l, sizeof(l), LONG_MIN, LONG_MAX);
    printf("unsigned long: %lu, 大小: %zu字节, 范围: 0-%lu\n", 
           ul, sizeof(ul), ULONG_MAX);
    
    // long long类型 - 通常为8字节
    long long ll = 9223372036854775807LL;
    unsigned long long ull = 18446744073709551615ULL;
    
    printf("\nlong long: %lld, 大小: %zu字节\n", ll, sizeof(ll));
    printf("unsigned long long: %llu, 大小: %zu字节\n", ull, sizeof(ull));
    
    printf("\n=== 固定宽度整型 (C99标准) ===\n");
    
    // 固定宽度整型 - 保证跨平台一致性
    int8_t i8 = 127;
    uint8_t ui8 = 255;
    int16_t i16 = 32767;
    uint16_t ui16 = 65535;
    int32_t i32 = 2147483647;
    uint32_t ui32 = 4294967295U;
    int64_t i64 = 9223372036854775807LL;
    uint64_t ui64 = 18446744073709551615ULL;
    
    printf("int8_t: %" PRId8 ", 大小: %zu字节\n", i8, sizeof(i8));
    printf("uint8_t: %" PRIu8 ", 大小: %zu字节\n", ui8, sizeof(ui8));
    printf("int16_t: %" PRId16 ", 大小: %zu字节\n", i16, sizeof(i16));
    printf("uint16_t: %" PRIu16 ", 大小: %zu字节\n", ui16, sizeof(ui16));
    printf("int32_t: %" PRId32 ", 大小: %zu字节\n", i32, sizeof(i32));
    printf("uint32_t: %" PRIu32 ", 大小: %zu字节\n", ui32, sizeof(ui32));
    printf("int64_t: %" PRId64 ", 大小: %zu字节\n", i64, sizeof(i64));
    printf("uint64_t: %" PRIu64 ", 大小: %zu字节\n", ui64, sizeof(ui64));
    
    printf("\n=== 数值系统表示 ===\n");
    int number = 155;
    printf("十进制: %d\n", number);
    printf("八进制: %o\n", number);
    printf("十六进制(小写): %x\n", number);
    printf("十六进制(大写): %X\n", number);
    printf("带前缀十六进制: %#x\n", number);
    printf("二进制表示: " BINARY_PATTERN "\n", BINARY(number));
    
    printf("\n=== 格式化输出控制 ===\n");
    printf("左对齐  : %-10d|\n", number);
    printf("右对齐  : %10d|\n", number);
    printf("显示符号: %+d\n", number);
    printf("前导零  : %010d\n", number);
    printf("字段宽度: %*d\n", 8, number);  // 动态宽度
}

/*
 * ========================================
 * 2. 浮点型数据类型详解
 * ========================================
 */
void demonstrate_floating_types() {
    SECTION_HEADER("2. 浮点型数据类型详解");
    
    printf("=== 基本浮点型 ===\n");
    
    // float - 单精度浮点数，通常4字节
    float f = 3.14159f;
    printf("float: %f, 大小: %zu字节\n", f, sizeof(f));
    printf("float精度: %d位有效数字\n", FLT_DIG);
    printf("float范围: %e ~ %e\n", FLT_MIN, FLT_MAX);
    printf("float epsilon: %e\n", FLT_EPSILON);
    
    // double - 双精度浮点数，通常8字节
    double d = 3.141592653589793;
    printf("\ndouble: %lf, 大小: %zu字节\n", d, sizeof(d));
    printf("double精度: %d位有效数字\n", DBL_DIG);
    printf("double范围: %e ~ %e\n", DBL_MIN, DBL_MAX);
    printf("double epsilon: %e\n", DBL_EPSILON);
    
    // long double - 扩展精度，大小因编译器而异
    long double ld = 3.141592653589793238L;
    printf("\nlong double: %Lf, 大小: %zu字节\n", ld, sizeof(ld));
    
    printf("\n=== 浮点数格式化输出 ===\n");
    double num = 123.456789;
    printf("%%f格式: %f\n", num);
    printf("%%e格式: %e\n", num);
    printf("%%E格式: %E\n", num);
    printf("%%g格式: %g\n", num);
    printf("%%G格式: %G\n", num);
    printf("指定精度: %.2f\n", num);
    printf("指定宽度: %10.2f\n", num);
    
    printf("\n=== 特殊浮点值 ===\n");
    
    // 正无穷
    float pos_inf = INFINITY;
    printf("正无穷: %f\n", pos_inf);
    
    // 负无穷
    float neg_inf = -INFINITY;
    printf("负无穷: %f\n", neg_inf);
    
    // NaN (Not a Number)
    float nan_val = sqrt(-1.0f);
    printf("NaN: %f\n", nan_val);
    
    // 检测特殊值
    if (isinf(pos_inf)) {
        printf("pos_inf 是无穷大\n");
    }
    if (isnan(nan_val)) {
        printf("nan_val 是NaN\n");
    }
    
    printf("\n=== 浮点精度问题 ===\n");
    float f1 = 1.0f / 3.0f;
    double d1 = 1.0 / 3.0;
    printf("float精度: %.20f\n", f1);
    printf("double精度: %.20lf\n", d1);
    
    // 浮点数比较问题
    float a = 0.1f + 0.2f;
    float b = 0.3f;
    printf("0.1 + 0.2 = %.20f\n", a);
    printf("0.3       = %.20f\n", b);
    printf("直接比较: %s\n", (a == b) ? "相等" : "不相等");
    printf("epsilon比较: %s\n", (fabs(a - b) < FLT_EPSILON) ? "相等" : "不相等");
}

/*
 * ========================================
 * 3. 字符型数据类型详解
 * ========================================
 */
void demonstrate_character_types() {
    SECTION_HEADER("3. 字符型数据类型详解");
    
    printf("=== 基本字符操作 ===\n");
    char ch = 'A';
    printf("字符: %c, ASCII值: %d\n", ch, ch);
    printf("字符大小: %zu字节\n", sizeof(ch));
    
    // 字符的数值性质
    printf("\n=== 字符与数值转换 ===\n");
    for (int i = 65; i <= 90; i++) {
        printf("%c ", i);
    }
    printf("\n");
    
    printf("\n=== 转义字符 ===\n");
    printf("换行符: \\n\n");
    printf("制表符: \\t\t制表符演示\n");
    printf("回车符: \\r演示\r被覆盖\n");
    printf("退格符: ABC\\b\\b删除\n");
    printf("响铃符: \\a\a\n");
    printf("双引号: \\\"\n");
    printf("单引号: \\'\n");
    printf("反斜杠: \\\\\n");
    printf("八进制: \\101 = %c\n", '\101');
    printf("十六进制: \\x41 = %c\n", '\x41');
    
    printf("\n=== 字符分类函数 ===\n");
    char test_chars[] = {'A', 'a', '5', ' ', '!', '\n'};
    int num_chars = sizeof(test_chars) / sizeof(test_chars[0]);
    
    for (int i = 0; i < num_chars; i++) {
        char c = test_chars[i];
        printf("字符 '%c' (ASCII %d):\n", 
               (c == '\n') ? ' ' : c, c);
        printf("  是字母: %s\n", isalpha(c) ? "是" : "否");
        printf("  是数字: %s\n", isdigit(c) ? "是" : "否");
        printf("  是字母数字: %s\n", isalnum(c) ? "是" : "否");
        printf("  是空白字符: %s\n", isspace(c) ? "是" : "否");
        printf("  是大写: %s\n", isupper(c) ? "是" : "否");
        printf("  是小写: %s\n", islower(c) ? "是" : "否");
        printf("\n");
    }
    
    printf("=== 字符转换 ===\n");
    char lower = 'a', upper = 'A';
    printf("小写转大写: %c -> %c\n", lower, toupper(lower));
    printf("大写转小写: %c -> %c\n", upper, tolower(upper));
}

/*
 * ========================================
 * 4. 布尔类型详解 (C99标准)
 * ========================================
 */
void demonstrate_boolean_types() {
    SECTION_HEADER("4. 布尔类型详解");
    
    printf("=== 基本布尔操作 ===\n");
    bool is_true = true;
    bool is_false = false;
    
    printf("bool类型大小: %zu字节\n", sizeof(bool));
    printf("true值: %d\n", is_true);
    printf("false值: %d\n", is_false);
    
    printf("\n=== 布尔值的隐式转换 ===\n");
    int numbers[] = {0, 1, -1, 42, 0};
    float floats[] = {0.0f, 1.0f, -1.5f, 0.1f, 0.0f};
    char* strings[] = {"", "hello", NULL};
    
    printf("整数转布尔:\n");
    for (int i = 0; i < 5; i++) {
        printf("  %d -> %s\n", numbers[i], numbers[i] ? "true" : "false");
    }
    
    printf("浮点数转布尔:\n");
    for (int i = 0; i < 5; i++) {
        printf("  %f -> %s\n", floats[i], floats[i] ? "true" : "false");
    }
    
    printf("指针转布尔:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %s -> %s\n", 
               strings[i] ? strings[i] : "NULL", 
               strings[i] ? "true" : "false");
    }
    
    printf("\n=== 逻辑运算 ===\n");
    bool a = true, b = false;
    printf("a = %s, b = %s\n", a ? "true" : "false", b ? "true" : "false");
    printf("a && b = %s\n", (a && b) ? "true" : "false");
    printf("a || b = %s\n", (a || b) ? "true" : "false");
    printf("!a = %s\n", (!a) ? "true" : "false");
    printf("!b = %s\n", (!b) ? "true" : "false");
    
    // 短路求值演示
    printf("\n=== 短路求值 ===\n");
    int x = 0, y = 0;
    if (++x && ++y) {
        printf("条件为真\n");
    }
    printf("x = %d, y = %d\n", x, y);  // x=1, y=1
    
    x = 0; y = 0;
    if (++x || ++y) {
        printf("条件为真\n");
    }
    printf("x = %d, y = %d\n", x, y);  // x=1, y=0 (短路)
}

/*
 * ========================================
 * 5. 类型转换详解
 * ========================================
 */
void demonstrate_type_conversions() {
    SECTION_HEADER("5. 类型转换详解");
    
    printf("=== 隐式类型转换 ===\n");
    
    // 整型提升
    char c = 100;
    short s = 200;
    int result = c + s;  // char和short被提升为int
    printf("char(%d) + short(%d) = int(%d)\n", c, s, result);
    
    // 算术转换
    int i = 10;
    float f = 3.14f;
    double d = i + f;  // int被转换为float，结果为double
    printf("int(%d) + float(%f) = double(%f)\n", i, f, d);
    
    // 符号性转换
    unsigned int ui = 4294967295U;  // UINT_MAX
    int si = ui;  // 可能导致数据丢失
    printf("unsigned int(%u) -> int(%d)\n", ui, si);
    
    printf("\n=== 显式类型转换（强制转换） ===\n");
    
    double big_double = 3.99;
    int truncated = (int)big_double;
    printf("double(%f) -> int(%d) [截断]\n", big_double, truncated);
    
    int negative = -1;
    unsigned int positive = (unsigned int)negative;
    printf("int(%d) -> unsigned int(%u)\n", negative, positive);
    
    // 指针类型转换
    int num = 0x12345678;
    char* byte_ptr = (char*)&num;
    printf("int值: 0x%x\n", num);
    printf("按字节读取: ");
    for (int i = 0; i < sizeof(int); i++) {
        printf("0x%02x ", (unsigned char)byte_ptr[i]);
    }
    printf("\n");
    
    printf("\n=== 类型转换的危险性 ===\n");
    
    // 精度丢失
    float precise = 12345678.9f;
    int lose_precision = (int)precise;
    printf("精度丢失: %f -> %d\n", precise, lose_precision);
    
    // 溢出
    int big_int = 300;
    char overflow = (char)big_int;
    printf("溢出: int(%d) -> char(%d)\n", big_int, overflow);
    
    // 截断
    double pi = 3.14159265359;
    float truncated_pi = (float)pi;
    printf("截断: double(%.11f) -> float(%.7f)\n", pi, truncated_pi);
}

/*
 * ========================================
 * 6. 输入输出格式化详解
 * ========================================
 */
void demonstrate_io_formatting() {
    SECTION_HEADER("6. 输入输出格式化详解");
    
    printf("=== printf格式化说明符 ===\n");
    
    int num = 42;
    float fnum = 3.14159f;
    char str[] = "Hello";
    char ch = 'A';
    
    // 基本格式化
    printf("整数: %%d = %d\n", num);
    printf("无符号整数: %%u = %u\n", (unsigned)num);
    printf("八进制: %%o = %o\n", num);
    printf("十六进制: %%x = %x, %%X = %X\n", num, num);
    printf("浮点数: %%f = %f\n", fnum);
    printf("科学计数法: %%e = %e, %%E = %E\n", fnum, fnum);
    printf("自适应: %%g = %g, %%G = %G\n", fnum, fnum);
    printf("字符: %%c = %c\n", ch);
    printf("字符串: %%s = %s\n", str);
    printf("指针: %%p = %p\n", (void*)&num);
    
    printf("\n=== 格式化控制符 ===\n");
    
    // 宽度控制
    printf("宽度控制:\n");
    printf("  %%10d: '%10d'\n", num);
    printf("  %%-10d: '%-10d'\n", num);
    printf("  %%010d: '%010d'\n", num);
    
    // 精度控制
    printf("精度控制:\n");
    printf("  %%.2f: %.2f\n", fnum);
    printf("  %%.10s: %.10s\n", str);
    printf("  %%10.2f: %10.2f\n", fnum);
    
    // 标志控制
    printf("标志控制:\n");
    printf("  %%+d: %+d\n", num);
    printf("  %% d: % d\n", num);
    printf("  %%#x: %#x\n", num);
    printf("  %%#o: %#o\n", num);
    
    printf("\n=== scanf输入格式化 ===\n");
    printf("scanf使用示例（注意：实际运行时需要输入）:\n");
    printf("scanf(\"%%d\", &number);  // 读取整数\n");
    printf("scanf(\"%%f\", &fnumber); // 读取浮点数\n");
    printf("scanf(\"%%c\", &character); // 读取字符\n");
    printf("scanf(\"%%s\", string);   // 读取字符串（不安全）\n");
    printf("scanf(\"%%10s\", string); // 限制长度读取\n");
    
    // scanf的危险性演示
    printf("\nscanf的问题和解决方案:\n");
    printf("1. 缓冲区溢出风险\n");
    printf("2. 输入验证困难\n");
    printf("3. 错误处理复杂\n");
    printf("建议使用fgets()或scanf_s()替代\n");
}

/*
 * ========================================
 * 7. 内存模型和存储类详解
 * ========================================
 */
void demonstrate_memory_model() {
    SECTION_HEADER("7. 内存模型和存储类详解");
    
    printf("=== 存储类说明符 ===\n");
    
    // auto（默认）
    auto int auto_var = 10;
    printf("auto变量（局部）: %d, 地址: %p\n", auto_var, (void*)&auto_var);
    
    // register建议（现代编译器通常忽略）
    register int reg_var = 20;
    printf("register变量: %d\n", reg_var);
    // printf("register地址: %p\n", (void*)&reg_var); // 可能出错
    
    // static局部变量
    static int static_local = 0;
    static_local++;
    printf("static局部变量: %d, 地址: %p\n", static_local, (void*)&static_local);
    
    // extern声明（在其他文件定义）
    // extern int global_var;  // 声明外部变量
    
    printf("\n=== 内存区域分布 ===\n");
    
    // 栈区域
    int stack_var = 100;
    printf("栈变量地址: %p\n", (void*)&stack_var);
    
    // 堆区域
    int* heap_var = (int*)malloc(sizeof(int));
    *heap_var = 200;
    printf("堆变量地址: %p, 值: %d\n", (void*)heap_var, *heap_var);
    free(heap_var);
    
    // 静态区域
    static int static_var = 300;
    printf("静态变量地址: %p\n", (void*)&static_var);
    
    // 常量区域
    const char* string_literal = "Hello World";
    printf("字符串常量地址: %p\n", (void*)string_literal);
    
    printf("\n=== 变量的生命周期 ===\n");
    {
        int block_var = 400;  // 块作用域
        printf("块变量: %d, 地址: %p\n", block_var, (void*)&block_var);
        
        static int block_static = 500;  // 静态生命周期
        block_static++;
        printf("块内静态变量: %d, 地址: %p\n", block_static, (void*)&block_static);
    }
    // block_var在此处不可访问
    // block_static仍然存在但不可访问
    
    printf("\n=== const和volatile ===\n");
    
    const int const_var = 600;
    printf("const变量: %d\n", const_var);
    // const_var = 700;  // 编译错误
    
    // 通过指针修改const（未定义行为）
    int* non_const_ptr = (int*)&const_var;
    *non_const_ptr = 700;
    printf("尝试修改const: %d\n", const_var);  // 结果不确定
    
    volatile int volatile_var = 800;
    printf("volatile变量: %d\n", volatile_var);
}

/*
 * ========================================
 * 8. 高级主题：位操作和内存布局
 * ========================================
 */
void demonstrate_advanced_topics() {
    SECTION_HEADER("8. 高级主题：位操作和内存布局");
    
    printf("=== 位操作详解 ===\n");
    
    unsigned char byte = 0b10101100;
    printf("原始字节: " BINARY_PATTERN " (%u)\n", BINARY(byte), byte);
    
    // 位与
    unsigned char mask = 0b00001111;
    unsigned char result = byte & mask;
    printf("位与操作: " BINARY_PATTERN " & " BINARY_PATTERN " = " BINARY_PATTERN "\n",
           BINARY(byte), BINARY(mask), BINARY(result));
    
    // 位或
    result = byte | mask;
    printf("位或操作: " BINARY_PATTERN " | " BINARY_PATTERN " = " BINARY_PATTERN "\n",
           BINARY(byte), BINARY(mask), BINARY(result));
    
    // 位异或
    result = byte ^ mask;
    printf("位异或: " BINARY_PATTERN " ^ " BINARY_PATTERN " = " BINARY_PATTERN "\n",
           BINARY(byte), BINARY(mask), BINARY(result));
    
    // 位取反
    result = ~byte;
    printf("位取反: ~" BINARY_PATTERN " = " BINARY_PATTERN "\n",
           BINARY(byte), BINARY(result));
    
    // 左移和右移
    result = byte << 2;
    printf("左移2位: " BINARY_PATTERN " << 2 = " BINARY_PATTERN "\n",
           BINARY(byte), BINARY(result));
    
    result = byte >> 2;
    printf("右移2位: " BINARY_PATTERN " >> 2 = " BINARY_PATTERN "\n",
           BINARY(byte), BINARY(result));
    
    printf("\n=== 结构体内存对齐 ===\n");
    
    struct unaligned {
        char c;      // 1字节
        int i;       // 4字节
        char c2;     // 1字节
    };
    
    struct aligned {
        int i;       // 4字节
        char c;      // 1字节
        char c2;     // 1字节
    };
    
    printf("未对齐结构体大小: %zu字节\n", sizeof(struct unaligned));
    printf("对齐结构体大小: %zu字节\n", sizeof(struct aligned));
    
    struct unaligned u = {'A', 12345, 'B'};
    printf("未对齐结构体成员地址:\n");
    printf("  c: %p (偏移: %zu)\n", (void*)&u.c, offsetof(struct unaligned, c));
    printf("  i: %p (偏移: %zu)\n", (void*)&u.i, offsetof(struct unaligned, i));
    printf("  c2: %p (偏移: %zu)\n", (void*)&u.c2, offsetof(struct unaligned, c2));
    
    printf("\n=== 大小端字节序 ===\n");
    
    union endian_test {
        int i;
        char c[4];
    };
    
    union endian_test test;
    test.i = 0x12345678;
    
    printf("整数值: 0x%x\n", test.i);
    printf("字节序: ");
    for (int i = 0; i < 4; i++) {
        printf("0x%02x ", (unsigned char)test.c[i]);
    }
    
    if (test.c[0] == 0x78) {
        printf("(小端序)\n");
    } else {
        printf("(大端序)\n");
    }
}

/*
 * ========================================
 * 9. 实用工具函数
 * ========================================
 */

// 打印内存内容的十六进制转储
void hex_dump(void* ptr, size_t size) {
    unsigned char* bytes = (unsigned char*)ptr;
    printf("内存转储 (地址: %p, 大小: %zu字节):\n", ptr, size);
    
    for (size_t i = 0; i < size; i += 16) {
        printf("%08zx: ", i);
        
        // 十六进制部分
        for (size_t j = 0; j < 16 && i + j < size; j++) {
            printf("%02x ", bytes[i + j]);
        }
        
        // 填充空格
        for (size_t j = size - i; j < 16 && j > 0; j++) {
            printf("   ");
        }
        
        printf(" |");
        
        // ASCII部分
        for (size_t j = 0; j < 16 && i + j < size; j++) {
            char c = bytes[i + j];
            printf("%c", (c >= 32 && c < 127) ? c : '.');
        }
        
        printf("|\n");
    }
}

// 类型信息打印
void print_type_info() {
    printf("\n=== 编译器类型信息 ===\n");
    printf("编译器: ");
    #ifdef __GNUC__
        printf("GCC %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #elif defined(_MSC_VER)
        printf("MSVC %d\n", _MSC_VER);
    #elif defined(__clang__)
        printf("Clang %s\n", __clang_version__);
    #else
        printf("未知\n");
    #endif
    
    printf("平台: ");
    #ifdef _WIN32
        printf("Windows ");
        #ifdef _WIN64
            printf("64位\n");
        #else
            printf("32位\n");
        #endif
    #elif defined(__linux__)
        printf("Linux\n");
    #elif defined(__APPLE__)
        printf("macOS\n");
    #else
        printf("未知\n");
    #endif
    
    printf("字节序: ");
    int test = 1;
    if (*(char*)&test == 1) {
        printf("小端序\n");
    } else {
        printf("大端序\n");
    }
    
    printf("指针大小: %zu字节\n", sizeof(void*));
    printf("size_t大小: %zu字节\n", sizeof(size_t));
}

/*
 * ========================================
 * 10. 测试和演示函数
 * ========================================
 */
void run_interactive_tests() {
    printf("\n=== 交互式测试 ===\n");
    printf("以下是一些可以手动测试的功能:\n\n");
    
    printf("1. 输入验证测试:\n");
    /*
    int number;
    printf("请输入一个整数: ");
    if (scanf("%d", &number) == 1) {
        printf("您输入的数字是: %d\n", number);
        printf("十六进制: 0x%x\n", number);
        printf("二进制: ");
        for (int i = 31; i >= 0; i--) {
            printf("%d", (number >> i) & 1);
            if (i % 4 == 0) printf(" ");
        }
        printf("\n");
    } else {
        printf("输入无效!\n");
    }
    */
    
    printf("2. 字符处理测试:\n");
    /*
    char ch;
    printf("请输入一个字符: ");
    scanf(" %c", &ch);  // 注意空格用于跳过空白字符
    printf("字符: %c, ASCII: %d\n", ch, ch);
    if (isalpha(ch)) {
        printf("这是一个字母\n");
        if (islower(ch)) {
            printf("小写字母，大写为: %c\n", toupper(ch));
        } else {
            printf("大写字母，小写为: %c\n", tolower(ch));
        }
    } else if (isdigit(ch)) {
        printf("这是一个数字\n");
    } else {
        printf("这是特殊字符\n");
    }
    */
    
    printf("3. 浮点精度测试:\n");
    /*
    float f_val;
    double d_val;
    printf("请输入一个小数: ");
    scanf("%f", &f_val);
    d_val = f_val;
    printf("float值: %.20f\n", f_val);
    printf("转为double: %.20lf\n", d_val);
    printf("差异: %e\n", fabs(d_val - f_val));
    */
}

// 性能测试函数
void performance_tests() {
    SECTION_HEADER("性能测试");
    
    const int iterations = 1000000;
    clock_t start, end;
    
    // 整数运算性能
    start = clock();
    volatile int sum1 = 0;
    for (int i = 0; i < iterations; i++) {
        sum1 += i;
    }
    end = clock();
    printf("整数加法 %d次: %f秒\n", iterations, 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // 浮点运算性能
    start = clock();
    volatile float sum2 = 0.0f;
    for (int i = 0; i < iterations; i++) {
        sum2 += (float)i;
    }
    end = clock();
    printf("浮点加法 %d次: %f秒\n", iterations, 
           ((double)(end - start)) / CLOCKS_PER_SEC);
    
    // 位运算性能
    start = clock();
    volatile int result = 0;
    for (int i = 0; i < iterations; i++) {
        result ^= i;
    }
    end = clock();
    printf("位异或 %d次: %f秒\n", iterations, 
           ((double)(end - start)) / CLOCKS_PER_SEC);
}

/*
 * ========================================
 * 主函数 - 程序入口点
 * ========================================
 */
int main() {
    printf("C语言完整教程 - 基础数据类型详解\n");
    printf("版本: v2.0.0\n");
    printf("编译时间: %s %s\n", __DATE__, __TIME__);
    
    // 打印系统信息
    print_type_info();
    
    // 演示各个主题
    demonstrate_integer_types();
    demonstrate_floating_types();
    demonstrate_character_types();
    demonstrate_boolean_types();
    demonstrate_type_conversions();
    demonstrate_io_formatting();
    demonstrate_memory_model();
    demonstrate_advanced_topics();
    
    // 内存转储示例
    SECTION_HEADER("内存转储示例");
    int sample_data[] = {0x12345678, 0xABCDEF00, 0x11223344};
    hex_dump(sample_data, sizeof(sample_data));
    
    // 性能测试
    performance_tests();
    
    // 交互式测试说明
    run_interactive_tests();
    
    printf("\n" "="*60 "\n");
    printf("教程完成！\n");
    printf("建议继续学习：函数、指针、数组等高级主题\n");
    printf("项目地址：https://github.com/username/C-Language-Tutorial\n");
    printf("="*60 "\n");
    
    return 0;
}