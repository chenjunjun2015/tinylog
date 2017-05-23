#include "adapter.h"
#include "layout.h"
#include "tinylog.h"
#include "catagory.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <fcntl.h>
#include <io.h>
#include <math.h>

#define DEFAULT_LOGFILE_MAXSIZE 50
#define DEFAULT_LOGFILE_RSIZE 30
#define DEFAULT_LOGFILE_RCOUNT 20

#define DEFAULT_ACCEPT _console_apt_accept
#define DEFAULT_FREE _free_console_apt

#define _adapter_addr(apt)\
    ((struct _adapter*)(&(apt) - (int)(((struct _adapter*)(NULL))->accept)))
#define _adapterprop_free(apt,prop,fucfree)\
    if(_adapter_addr(apt)->prop){\
        fucfree(_adapter_addr(apt)->prop);\
    }

adapter_accept
_create_null_adapter(){
    struct _adapter* apt =
        (struct _adapter*)malloc(sizeof(struct _adapter*));
    if (!apt) return NULL;
    apt->accept = DEFAULT_ACCEPT;
    apt->free = DEFAULT_FREE;
    return apt->accept;
}

void
_free_adapter(adapter_accept apt){
    struct _adapter* _apt = _adapter_addr(apt);
    if (_apt->free){
        _apt->free(apt);
    }
}

const ls_t 
_get_apt_name(adapter_accept apt){
	return _adapter_addr(apt)->name;
}

adapter_free
_get_apt_free(adapter_accept apt){
    return _adapter_addr(apt)->free;
}

layout_callback 
_get_apt_layout(adapter_accept apt)
{
	return _adapter_addr(apt)->layout;
}

struct _catagory*
_get_apt_catagory(adapter_accept apt){
    return _adapter_addr(apt)->catagory;
}

int 
_set_apt_name(adapter_accept apt,const char* name)
{
	struct _adapter* _apt = _adapter_addr(apt);
	if (_apt->name) {
		lsfree(_apt->name);
	}
	_apt->name = lscreate(name, strlen(name));
	return 0;
}

void
_set_apt_catagory(adapter_accept apt,struct _catagory* catagory){
    _adapter_addr(apt)->catagory = catagory;
}

int
_set_apt_file(adapter_accept apt, const char* logfile){
    if (_adapter_addr(apt)->_file.logfile = lscreate(logfile, strlen(logfile))){
        return 0;
    }
    return -1;
}

int
_set_apt_maxsize(adapter_accept apt, long maxsize){
    _adapter_addr(apt)->maxsize = maxsize;
    return 0;
}

int
_set_apt_rcount(adapter_accept apt, long rcount){
    _adapter_addr(apt)->rcount = rcount;
    return 0;
}

int
_set_apt_dcount(adapter_accept apt, int days){
    _adapter_addr(apt)->maxday = days;
    return 0;
}

int
_set_apt_dayfmt(adapter_accept apt, const char* fmt){
    _adapter_addr(apt)->dayfmt = lscreate(fmt,strlen(fmt));
    return 0;
}

int
_set_apt_stream(adapter_accept apt, int stream){
    _adapter_addr(apt)->_stream = stream;
    return 0;
}

void
_set_apt_layout(adapter_accept apt, layout_callback layout){
    _adapter_addr(apt)->layout = layout;
}

adapter_accept
_create_null_file_apt(const char* name,const char* logfile){
    struct _adapter* apt =
        (struct _adapter*)malloc(sizeof(struct _adapter*));
    if (!apt) return NULL;
    apt->name = lscreate(name, strlen(name));
    apt->accept = _file_apt_accept;
    apt->free = _free_file_apt;
    apt->flag = O_APPEND | O_WRONLY | O_CREAT | O_TRUNC;
    apt->mode = O_TEXT | O_NOINHERIT;
    apt->logfile = lscreate(logfile, strlen(logfile));
    apt->maxsize = DEFAULT_LOGFILE_MAXSIZE;
    apt->layout = create_base_layout(apt->accept);
    apt->maxsize = DEFAULT_LOGFILE_MAXSIZE;
    if (apt->fd = _open(apt->logfile, apt->flag, apt->mode)){
        _adapterprop_free(apt, name, lsfree);
        _adapterprop_free(apt, logfile, lsfree);
        free(apt);
        return NULL;
    }
    apt->fsize = _filelength(apt->fd);
    
    return apt->accept;
}

adapter_accept
_create_file_apt(const char* name, struct _catagory* cata, const char* logfile, int maxsize){
    struct _adapter* apt =
        (struct _adapter*)malloc(sizeof(struct _adapter*));
    if (!apt) return NULL;
    apt->name = lsinitcpy(name);
    apt->accept = _file_apt_accept;
    apt->free = _free_file_apt;
    if (apt->logfile = lscreate(logfile, strlen(logfile))){
        free(apt);
        return NULL;
    }
    apt->maxsize = maxsize;
    apt->layout = create_base_layout(apt->accept);
    apt->flag = O_APPEND | O_WRONLY | O_CREAT | O_TRUNC;
    apt->mode = O_TEXT | O_NOINHERIT;

    if (apt->fd = _open(apt->logfile, apt->flag, apt->mode)){
        _adapterprop_free(apt, name, lsfree);
        _adapterprop_free(apt, logfile, lsfree);
        free(apt);
        return NULL;
    }
    apt->fsize = _filelength(apt->fd);
    if (cata) {
        addAdapter(cata, apt);
        apt->catagory = cata;
    }
    return apt->accept;
}

int
_free_file_apt(adapter_accept apt){
    _adapterprop_free(apt, name, lsfree);
    _adapterprop_free(apt, logfile, lsfree);
    free(_adapter_addr(apt));
    return 0;
}

int
_file_apt_accept(adapter_accept apt,struct _log_msg* msg){
    if (!apt || !msg) return -1;
    struct _adapter* _apt = _adapter_addr(apt);
    ls_t ls = (_apt->layout)(_apt->layout,msg);
	_apt->fsize += lslen(ls);
	if (_apt->fsize >= _apt->maxsize*1024*1024) {
        _apt->fd = _open(_apt->logfile, _apt->flag | O_TRUNC | O_APPEND, _apt->mode);
		_apt->fsize = 0;
	}
    _write(_apt->fd, ls, lslen(ls));
    lsfree(ls);
    return 0;
}

adapter_accept
_create_null_rfile_apt(const char* name,const char* logfile){
    struct _adapter* apt =
        (struct _adapter*)malloc(sizeof(struct _adapter*));
    if (!apt) return NULL;
    apt->logfile = lsinitcpy(logfile);
    apt->name = lsinitcpy(name);
    apt->flag = O_APPEND | O_WRONLY | O_CREAT;
    apt->mode = O_TEXT | O_NOINHERIT;
    apt->index = 0;
    apt->rcount = DEFAULT_LOGFILE_RCOUNT;
    apt->maxsize = DEFAULT_LOGFILE_RSIZE;
    apt->extw = (long)log10(apt->rcount) + 1;
    ls_t back_path = lsinitcpyls(apt->logfile);
    for (; apt->index < apt->rcount; apt->index++){
        back_path = lscatfmt(back_path, ".%.*s",apt->extw,apt->index+1);
        if (!_access(back_path, 0)){
            break;
        }
    }
    lsfree(back_path);
    int fd = _open(apt->logfile, apt->flag, apt->mode);
    if (!fd){
        _adapterprop_free(apt, name, lsfree);
        _adapterprop_free(apt, logfile, lsfree);
        free(apt);
        return NULL;
    }

    apt->fsize = _filelength(fd);
    apt->fd = fd;
    apt->accept = _rfile_apt_accept;
    apt->free = _free_rfile_apt;
    apt->layout = create_base_layout(apt->accept);

    return apt->accept;
}

adapter_accept
_create_rfile_apt(const char* name,struct _catagory* cata, const char* logfile, long rsize, long rcount){
    struct _adapter* apt =
        (struct _adapter*)malloc(sizeof(struct _adapter*));
    if (!apt) return NULL;
    apt->logfile = lsinitcpy(logfile);
    apt->name = lsinitcpy(name);
    apt->fsize = rsize;
    apt->flag = O_APPEND | O_WRONLY | O_CREAT;
    apt->mode = O_TEXT | O_NOINHERIT;
    apt->index = 0;
    apt->rcount = rcount <= 0? 1: rcount;
    apt->extw = (long)log10(apt->rcount) + 1;
    ls_t back_path = lsinitcpyls(apt->logfile);
    for (; apt->index < apt->rcount; apt->index++){
        back_path = lscatfmt(back_path, ".%.*s",apt->extw,apt->index+1);
        if (!_access(back_path, 0)){
            break;
        }
    }
    lsfree(back_path);
    int fd = _open(apt->logfile, apt->flag, apt->mode);
    if (!fd){
        _adapterprop_free(apt, name, lsfree);
        _adapterprop_free(apt, logfile, lsfree);
        free(apt);
        return NULL;
    }

    apt->layout = basicLayout;
    apt->accept = _rfile_apt_accept;
    apt->free = _free_rfile_apt;
    if (cata) {
        addAdapter(cata, apt);
        apt->catagory = cata;
    }
    return apt->accept;
}

int
_free_rfile_apt(adapter_accept apt){
    return _free_file_apt(apt);
}

int 
_rolling_over(struct _adapter* apt){
    if (!apt) return -1;
    ls_t back_path = lsinitfmt(apt->logfile,".%.*d",apt->extw,1);
    if (apt->index + 1 >= apt->rcount){
        remove(back_path);
        for (int i = 1; i < apt->rcount; i++){
            ls_t path_old = lsinitfmt("%s.%.*d", apt->logfile, i + 1);
            if (!_access(path_old, 0)){
                ls_t path_new = lsinitfmt("%s.%.*d", apt->logfile, i);
                rename(path_old, path_new);
                lsfree(path_old);
                lsfree(path_new);
            } else{
                break;
            }
        }
        rename(apt->logfile, back_path);
        lsfree(back_path);
        return 0;
    }
    rename(apt->logfile, back_path);
    apt->index++;
    lsfree(back_path);
    return 0;
}

int
_rfile_apt_accept(adapter_accept apt, struct _log_msg* msg){
    if (!apt || !msg) return -1;
    struct _adapter* _apt = _adapter_addr(apt);
    ls_t ls = (_apt->layout)(_apt->layout,msg);
	if (_apt->fsize + lslen(ls) >= _apt->maxsize*1024*1024) {
        _close(_apt->fd);
        _rolling_over(_apt);
		_apt->fsize = 0;
        _apt->fd = _open(_apt->logfile, _apt->flag, _apt->mode);
        if (!_apt->fd) {
            lsfree(ls);
            return -2;
        }
	}
    _write(_apt->fd, ls, lslen(ls));
    _apt->fsize += strlen(ls);
    lsfree(ls);
	return 0;
}

adapter_accept
_create_null_console_apt(const char* name , int stream){
    struct _adapter* apt =
        (struct _adapter*)malloc(sizeof(struct _adapter*));
    if (!apt) return NULL;
    apt->accept = _console_apt_accept;
    apt->free = _free_console_apt;
    apt->name = lscreate(name, strlen(name));
    apt->_stream = stream;

    return apt->accept;
}

adapter_accept
_create_console_apt(const char* name,struct _catagory* cata){
    struct _adapter* apt =
        (struct _adapter*)malloc(sizeof(struct _adapter*));
    if (!apt) return NULL;
    apt->name = lsinitcpy(name);
    apt->accept = _console_apt_accept;
    apt->free = _free_console_apt;
    apt->name = lsinitcpy(name);

    if (cata) {
        addAdapter(cata, apt);
        apt->catagory = cata;
    }
    return apt->accept;
}

int
_console_apt_accept(adapter_accept apt, struct _log_msg* msg){
    struct _adapter* _apt = _adapter_addr(apt);
    ls_t ls = (*_apt->layout)(_apt->layout, msg);
    fprintf((FILE*)_apt->fd, "%s", ls);
    lsfree(ls);
    return 0;
}

int
_free_console_apt(adapter_accept apt){
    if (!apt) return 0;
    _adapterprop_free(apt, name, lsfree);
    free(_adapter_addr(apt));
    return 0;
}

