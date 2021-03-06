
#ifndef LOG_LAYOUT_HH
#define LOG_LAYOUT_HH

#include "logstr.h"
#include "tick.h"

/**
 * @author
 *      j.j.chen
 * @date
 *      4/30/2017
 * @note
 *      layout 是一个日志消息布局器，每一条日志消息都包含有其他一些附属信息，
 *      比如消息的优先级，消息经过的分类器，消息产生的时间等等。layout就是将
 *      这些信息进行整合，按照一定格式输出为一条日志消息。
 *      struct _layout为整个layout的结构体，具体的实现由layout_priv_t来
 *      实现。
 *      当前实现的由basiclayout以及patternlayout。
 */

struct _log_msg;
struct _logger;
struct _log_ts;
struct _layout;
typedef void* layout_priv_t;
typedef ls_t(*layouting)(struct _layout* ,struct _log_msg* );
typedef void(*layout_priv_free)(layout_priv_t);
struct _layout {
    layouting layout;
    struct _log_ts ts;
    layout_priv_t priv;
    layout_priv_free privfree;
};
typedef struct _layout* _layout_t;

struct _pattern_layout_priv {
    ls_t pattern;
};
typedef struct _pattern_layout_priv* _lyt_pattern_priv_t;
typedef void* _lyt_basic_priv_t;

/**
 * @brief
 *      创建一个日志布局器，并将该布局器添加到日志输出器logger中
 * @param logger
 *      需要添加日志布局器的日志输出器
 * @return
 *      返回该布局器
 */
_layout_t
_create_layout(struct _logger* logger);

/**
 * @brief
 *      释放layout
 */
void
_free_layout(_layout_t layout);


/**
 * @brief
 *      创建一个基础布局器的实现方式
 */
_lyt_basic_priv_t
_create_basic_layout_impl(_layout_t layout);


/**
 * @brief
 *      创建一个模式布局器的实现方式
 * @param layout
 * @return
 */
_lyt_pattern_priv_t
_create_pattern_layout_impl(_layout_t layout);

/**
 * @brief
 *      释放模式布局器的实现方式
 */
void
_free_pattern_layout_impl(layout_priv_t layout);

/**
 * @brief
 *      获取模式布局器中的模式
 */
const char*
_get_layout_pattern(layout_priv_t priv);

/**
 * @brief
 *      设置模式布局器中的模式
 */
void
_set_layout_pattern(layout_priv_t priv,const char* pattern);

/**
 * @brief
 *      创建一个属于logger的模式为pattern的模式布局器，并返回该布局器
 */
_layout_t
_create_pattern_layout(struct _logger* logger, ls_t pattern);

/**
 * @brief
 *      创建一个属于logger的基础布局器
 */
_layout_t
_create_base_layout(struct _logger* logger);


/**
 * Sets the format of log lines handled by this
 * PatternLayout. By default, set to "%%m%%n".<br>
 * Format characters are as follows:<br>
 * <li><b>%%</b> - a single percent sign</li>
 * <li><b>%%c</b> - the category</li>
 * <li><b>%%d</b> - the date\n
 *  Date format: The date format character may be followed by a date format
 *  specifier enclosed between braces. For example, %%d{%%H:%%M:%%S,%%l} or %%d{%%d %%m %%Y %%H:%%M:%%S,%%l}.
 *  If no date format specifier is given then the following format is used:
 *  "Wed Jan 02 02:03:55 1980". The date format specifier admits the same syntax
 *  as the ANSI C function strftime, with 1 addition. The addition is the specifier
 *  %%l for milliseconds, padded with zeros to make 3 digits.</li>
 * <li><b>%%m</b> - the message</li>
 * <li><b>%%n</b> - the platform specific line separator</li>
 * <li><b>%%p</b> - the priority</li>
 * <li><b>%%r</b> - milliseconds since this layout was created.</li>
 * <li><b>%%R</b> - seconds since Jan 1, 1970</li>
 * <li><b>%%u</b> - clock ticks since process start</li>
 * <li><b>%%x</b> - the NDC</li>
 * @param conversionPattern the conversion pattern
 * @exception ConfigureFailure if the pattern is invalid

 * represent the time specified in timeptr. They all begin 
 * with a percentage (%) sign, and are:
 * specifier	Replaced by	                              Example
 * %a	        Abbreviated weekday name *	              Thu
 * %A	        Full weekday name *	                      Thursday
 * %b			Abbreviated month name *	              Aug
 * %B			Full month name *	                      August
 * %c			Date and time representation *	          Thu Aug 23 14:55:02 2001
 * %d			Day of the month (01-31)	              23
 * %H			Hour in 24h format (00-23)	              14
 * %I			Hour in 12h format (01-12)	              02
 * %j			Day of the year (001-366)	              235
 * %m			Month as a decimal number (01-12)	      08
 * %M			Minute (00-59)	                          55
 * %p			AM or PM designation	                  PM
 * %S			Second (00-61)	                          02
 * %U			Week number with the first Sunday as
 *              the first day of week one (00-53)	      33
 * %w			Weekday as a decimal number with 
 *              Sunday as 0 (0-6)	                      4
 * %W			Week number with the first Monday as 
 *              the first day of week one (00-53)	      34
 * %x			Date representation *	                  08/23/01
 * %X			Time representation *	                  14:55:02
 * %y			Year, last two digits (00-99)	          01
 * %Y			Year	                                  2001
 * %Z			Timezone name or abbreviation	          CDT
 * %%			A % sign	                              %
 */
ls_t 
_pattern_layout(struct _layout* layout ,struct _log_msg* msg);

/**
 * @brief
 *      基础布局器布局日志消息，在基础布局器中，每条日志消息被规范成了[priority][catagory][msg]的模式。
 */
ls_t
_basic_layout(struct _layout* layout ,struct _log_msg* msg);

#endif//LOG_LAYOUT_HH
