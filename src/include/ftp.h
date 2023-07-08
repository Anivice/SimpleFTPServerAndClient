#ifndef FTPSRVCLI_FTP_H
#define FTPSRVCLI_FTP_H

#include <vector>
#include <string>
#include <network_session.h>

/* Commands enumeration */
enum cmdlist
{
    ABOR, CWD, DELE, LIST, MDTM, MKD, NLST, PASS, PASV,
    PORT, PWD, QUIT, RETR, RMD, RNFR, RNTO, SITE, SIZE,
    STOR, TYPE, USER, NOOP
};

/* String mappings for cmdlist */
static const char *cmdlist_str[] =
{
        "ABOR", "CWD", "DELE", "LIST", "MDTM",
        "MKD", "NLST", "PASS", "PASV", "PORT",
        "PWD", "QUIT", "RETR", "RMD", "RNFR",
        "RNTO", "SITE", "SIZE", "STOR", "TYPE",
        "USER", "NOOP"
};

cmdlist strcmd2numcmd(const char *);

typedef void do_operations_t(server_session session);

do_operations_t do_abor;
do_operations_t do_cwd;
do_operations_t do_dele;
do_operations_t do_list;
do_operations_t do_mdtm;
do_operations_t do_mkd;
do_operations_t do_nlst;
do_operations_t do_pass;
do_operations_t do_pasv;
do_operations_t do_port;
do_operations_t do_pwd;
do_operations_t do_quit;
do_operations_t do_retr;
do_operations_t do_rmd;
do_operations_t do_rnfr;
do_operations_t do_rnto;
do_operations_t do_site;
do_operations_t do_size;
do_operations_t do_stor;
do_operations_t do_type;
do_operations_t do_user;
do_operations_t do_noop;

extern void (*react_table[])(server_session session);

#endif //FTPSRVCLI_FTP_H
