#include <ftp.h>
#include <simple_err.h>
#include <iostream>

void (*react_table[])(server_session session)
        {
                do_abor, do_cwd, do_dele, do_list, do_mdtm, do_mkd,
                do_nlst, do_pass, do_pasv, do_port, do_pwd, do_quit,
                do_retr, do_rmd, do_rnfr, do_rnto, do_site, do_size,
                do_stor, do_type, do_user, do_noop
        };

void react(server_session session)
{
    try
    {
        char cmd[16] {};
        session.read(cmd, sizeof (cmd));
        auto n_cmd = strcmd2numcmd(cmd);
        (*react_table[n_cmd])(session);
    }
    catch (simple_error_t & error)
    {
        std::cerr << error.what() << std::endl;
    }

    session.close();
}

void do_abor (server_session session)
{
}

void do_cwd (server_session session)
{
}

void do_dele (server_session session)
{
}

void do_list (server_session session)
{
}

void do_mdtm (server_session session)
{
}

void do_mkd (server_session session)
{
}

void do_nlst (server_session session)
{
}

void do_pass (server_session session)
{
}

void do_pasv (server_session session)
{
}

void do_port (server_session session)
{
}

void do_pwd (server_session session)
{
}

void do_quit (server_session session)
{
}

void do_retr (server_session session)
{
}

void do_rmd (server_session session)
{
}

void do_rnfr (server_session session)
{
}

void do_rnto (server_session session)
{
}

void do_site (server_session session)
{
}

void do_size (server_session session)
{
}

void do_stor (server_session session)
{
}

void do_type (server_session session)
{
}

void do_user (server_session session)
{
}

void do_noop (server_session session)
{
}
