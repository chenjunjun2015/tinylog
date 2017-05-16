#ifndef J_LOG_STR_HH
#define J_LOG_STR_HH

/**
 * @author j.j.c
 * @date 4/12/2017
 * @note
 *      1. logstr�ַ�����һ����C�ַ������м��װ�װ���ַ������������ϡ�
 *      2. ÿ��logstr�ַ�������Ҫ��ʹ�ý�����ͨ��lsfree�����ͷš�
 *      3. �ڴ������������ڴ����һ�������뷵�����Ͳ�����Ϊls_t�ĺ���ʱ��
 *         �������Խ��Ϊself������ֵҲ��self�����Ǵ����self�뷵�ص�self
 *         ��ַ���ܲ�һ������ˣ�ʹ��ʱ����ã���أ�ʹ��������ʽ���е��á�
 *         exp��   ls_t s = lsfunc(s,param);
 */


typedef char* ls_t;
struct logstr{
    int len;
    int free;
    char str[];
};

/**
 * @brief
 *      ���ڳ�ʼ��logstr���൱�ڴ���һ��logstr����
 * @param c
 *      �������logstr������ڴ�ռ䡣
 * @param len
 *      ȷ��logstr���ڴ�ռ��С�����ַ�������ĳ��ȡ�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      ls_t s1 = lsint('a',5);
 *      s1 == "aaaaa";
 * @note
 *      ÿһ��������logstr������Ҫͨ��lsfree���ͷ��ڴ档
 * @see
 *      lsinit,lsmkempty,lscreate,lsinitfmt,lsfree
 */
ls_t 
lsinit(char c, int len);


/**
 * @brief
 *      ����һ���յ�logstr�ַ�����
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      ls_t emy = ls_mkempty();
 *      emy == "";
 * @note
 *      �����ǿյ��ַ�����Ҳ��Ҫͨ��lsfree���ͷš�
 * @see
 *      lsinit,lsmkempty,lscreate,lsinitfmt,lsfree
 */
ls_t
lsmkempty();


/**
 * @brief
 *      ͨ���ɱ��������ʼ��һ��logstr����
 * @param fmt
 *      ��ʽ���ַ�������������֪��C����printf��ʽһ�¡�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      ls_t s1 = lsinitfmt("%d,%s",2017,"Welcome!");
 *      s1 == "2017,Welcome!";
 * @note
 *      ÿһ��������logstr������Ҫͨ��lsfree���ͷ��ڴ档
 * @see
 *      lsinit,lsmkempty,lscreate,lsinitfmt,lsfree
 */
ls_t
lsinitfmt(char* fmt, ...);


/**
 * @brief
 *      ͨ�����е�����������logstr����
 * @param str
 *      ���ڹ���logstr��������ݵ�ַ��
 * @param len
 *      �������ݵĳ��ȡ�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      ls_t s1 = lscreate('Hello World!',12);
 *      s1 == "Hello World!";
 * @note
 *      ÿһ��������logstr������Ҫͨ��lsfree���ͷ��ڴ档
 * @see
 *      lsinit,lsmkempty,lscreate,lsinitfmt,lsfree
 */
ls_t 
lscreate(const void* str,int len);


/**
 * @brief
 *      Ϊ���е�logstr���󴴽�����ı��ÿռ䡣
 * @param ls
 *      ��Ҫ��������ռ���ַ�����
 * @param room
 *      ������Ҫ�Ŀռ�ߴ��С.
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      ls_t s1 = lsint('a',5);
 *      s1 == "aaaaa";
 *      lssize(s1) == 5;
 *      s1 = lsmkroom(s1,12);
 *      lssize(s1) == 17;
 *      lsavil(s1) == 12;
 * @see
 *      lsinit,lsmkempty,lscreate,lsinitfmt,lsfree
 */
ls_t
lsmkroom(ls_t ls, int room);


/**
 * @brief
 *      �ͷ�logstr������ڴ�ռ䡣ÿһ��logstr������Ҫ��ʹ�ý���������ͷš�
 * @param ls
 *      ��Ҫ�����ڴ�ռ��ͷŵ��ַ�����
 * @exzample
 *      ls_t s1 = lsint('a',5);
 *      lsfree(s1);
 * @note
 *      ÿһ��������logstr������Ҫͨ��lsfree���ͷ��ڴ档
 * @see
 *      lsinit,lsmkempty,lscreate,lsinitfmt,lsfree
 */
void 
lsfree(ls_t ls);


/**
 * @brief
 *      ���ڷ���logstr�ַ����ĳ��ȣ��൱��C����strlen��
 * @param ls
 *      ��Ҫ�����س��ȵ��ַ�����
 * @return
 *      ls�ַ����ĳ��ȡ�
 * @exzample
 *      ls_t s1 = lsint('a',5);
 *      5 == lslen(s1);
 * @note
 *      �μ�struct logstr����
 * @see
 *      lsresize,lssize,lslen,lsavil,lsmemsize
 */
int 
lslen(const ls_t ls);


/**
 * @brief
 *      ���ڷ���logstr�ַ������ÿռ�ĳ���.
 * @param ls
 *      ��Ҫ�����ؿ��ÿռ䳤�ȵ��ַ�����
 * @return
 *      ls�ַ����Ŀ��ÿռ䳤�ȡ�
 * @exzample
 *      ls_t s1 = lsint('a',5);
 *       s1 = lsmkroom(s1,3);
 *       3 == lsavil(s1);
 * @note
 *      �μ�struct logstr����
 * @see
 *      lsresize,lssize,lslen,lsavil,lsmemsize
 */
int
lsavil(const ls_t ls);


/**
 * @brief
 *      ����logstr�ַ������׵�ַ��
 * @exzample
 *      ls_t s1 = lscreate("Hello World!",12);
 *      s1 == lsbegin(s1);
 * @see
 *      lsend
 */
char*
lsbegin(const ls_t ls);


/**
 * @brief
 *      ����logstr�ַ�����β����ַ��
 * @see
 *      lsbegin
 */
char*
lsend(const ls_t ls);


/**
 * @brief
 *      ����logstr�ַ����Ŀռ�ߴ磬�����ַ�����������ÿռ䡣
 * @exzample
 *      lslen(s)+lsavil(s) == lssize(s)
 * @note
 * @see
 *      lslen,lsavil
 */
int 
lssize(const ls_t ls);


/**
 * @brief
 *      ����logstr�ַ�����ռ�õ��ڴ�ռ�ߴ硣�����ַ����ߴ��Լ��ṹ������ڴ档
 * @exzample
 *      lsmemsize(s) == lssize(s)+sizeof(struct logstr)+1
 * @see
 *      lslen,lsavil,lssize
 */
int 
lsmemsize(const ls_t ls);


/**
 * @brief
 *      ��������ռ䲢��䡣
 * @param c
 *      �������logstr������ڴ�ռ䡣
 * @param size
 *      ȷ��logstr���ڴ�ռ��С�����ַ�������ĳ��ȡ�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      ls_t s = lsmkempty();
 *      s = lsresize(s,0,5);
 *      5 == lssize(5);
 * @note
 *      ...
 */
ls_t
lsresize(ls_t ls,char c, int size);


/**
 * @brief
 *      ���logstr�ַ������������������ַ���������Ӱ�����ڴ�ռ�ı䶯��
 */
void
lsclear(ls_t ls);

/**
 * @brief
 *      �����ַ�������str�ַ��������ݿ�����ls�С�
 * @note
 *      �����ַ������ܻ�Ӱ�쵽ԭ��logstr�ַ������ڴ�ռ䣬�����ַ�������ԶԶС������
 *      logstr�ַ����Ŀռ�ʱ��logstr�ַ����ռ����н���������
 * @see
 *      lscpyls
 */
ls_t 
lscpy(ls_t ls,const char* str);


/**
 * @brief
 *      �����ַ�������str�ַ��������ݿ�����ls�С�
 * @note
 *      1.�����ַ������ܻ�Ӱ�쵽ԭ��logstr�ַ������ڴ�ռ䣬�����ַ�������ԶԶС������
 *      logstr�ַ����Ŀռ�ʱ��logstr�ַ����ռ����н���������
 *      2.��lscpy��ͬ����lscpyls��ʾ����������Դ����Ҳ��һ��logstr
 * @see
 *      lscpyls
 */
ls_t
lscpyls(ls_t ls, const ls_t str);


/**
 * @brief
 *      �����Ƚ������ַ���������ͬʱ����0����C ����strcmp��memcmp���ơ�
 */
int 
lscmp(const ls_t left, const char* right);


/**
 * @brief
 *      �����Ƚ������ַ���������ͬʱ����0����C ����strcmp��memcmp���ơ�
 * @note
 *      ��lscmp��ͬ����lscmpls��ʾ����������Դ����Ҳ��һ��logstr
 */
int 
lscmpls(const ls_t left, const ls_t right);


/**
 * @brief
 *      ��str�ַ������ӵ�ls�ַ���β�������ء�
 */
ls_t 
lscat(ls_t ls,const char* str);


/**
 * @brief
 *      ��str�ַ������ӵ�ls�ַ���β�������ء�
 * @note
 *      ��lscat��ͬ����lscatls��ʾ����������Դ����Ҳ��һ��logstr
 */
ls_t
lscatls(ls_t ls, const ls_t str);

/**
 * @brief
 *      ��str�ַ������ӵ�ls�ַ���β�������ء�
 * @note
 *      ��lscat��ͬ����lscatls��ʾ����������Դ���ݵ�һ�����ȣ�������ȫ����
 */
ls_t
lscatlen(ls_t ls, const char* str, int len);


/**
 * @brief
 *      ��ls�ַ���ȫ��ת��ΪСд��ĸ��������
 */
ls_t
lslower(ls_t ls);


/**
 * @brief
 *      ��ls�ַ���ȫ��ת��Ϊ��д��ĸ��������
 */
ls_t
lsupper(ls_t ls);


/**
 * @brief
 *      ����ls�ַ�������β���ַ���������
 */
ls_t
lstrim(ls_t ls);


/**
 * @brief
 *      ͨ���ɱ����������һ���ַ�����
 * @param fmt
 *      ��ʽ���ַ�������������֪��C����printf��ʽһ�¡�
 * @return
 *      ����logstr��������ݣ��ַ������ռ��ַ��
 * @exzample
 *      s1 == "Here we come";
 *      ls_t s1 = lscatfmt(s1 ,"%d,%s",2017,"Welcome!");
 *      s1 == "Here we come2017,Welcome!";
 * @note
 *      
 * @see
 *      lsinit,lsmkempty,lscreate,lsinitfmt,lsfree
 */
ls_t 
lscatfmt(ls_t ls, char* fmt, ...);


/**
 * @brief
 *      ��ls�ַ������½��и�ʽ����
 * @exzample
 * @note
 */
ls_t 
lsformat(ls_t ls,char* fmt, ...);


/**
 * @brief
 *      �ַ����Ŀ��ӻ�������snprintf.cʵ�֡�
 * @param size
 *      ���봫��һ���������Ҳ���ΪNULL��������һ��size֮�����Ȼ��ɸ�size������̽�Եĸ�ʽ����
 *      ����ռ䲻������size���з���������㹻���򷵻������ָ���ַ��
 * @return
 *      ���ظ�ʽ��֮����ַ����ĵ�ַ
 */
char*
_ls_va_buffer( int* size,char* fmt, char* args);

#endif//J_LOG_STR_HH