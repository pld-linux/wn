/********************************************************
 * CONFIGURATION FILE FOR THE WN PACKAGE (vers 2.4.6)
 *
 * wn-config.h.dist-version 2.4.6
 * (this is used to indicate backward compatibility)
 ********************************************************/

/********************************************************
 * Compulsory items to fill in.
 ********************************************************/


#define LINUX		/* Operating System */
/*
   Pick one of the following Operating System types which describes
   your system and replace the SUN_OS4 value above

   AIX, AUX, BSDI, CONVEX_0S, DYNIX, FREE_BSD, HPUX, ISC, LINUX, 
   NET_BSD, NEXT, OPEN_BSD, OSF1, PYRAMID, RISCOS, SCO, SGI, SINIX, SOLARIS,
   SUN_OS4, SVR4, ULTRIX, UNIXWARE, UXPDS, OTHER

   I have no way to test all these, let me know if something doesn't work
   or is incomplete.  If you pick OTHER you must edit the last few lines
   of this file per the directions there.

   If you pick SOLARIS, SCO, UNIXWARE, NET_BSD, or FREE_BSD you will
   need to edit the Makefile also.
*/


#define ROOT_DIR	"/home/services/httpd"
/*
 * Enter the complete path of your root data directory here.
 */

#define WN_LOGFILE	"/var/log/wn/wn_access.log"
#define WN_ERRLOGFILE	"/var/log/wn/wn_error.log"

/*
 * Full path of the file you want to use for a log file and the
 * file for an errorlog. Comment out these lines to turn off logging.  
 * The values set here are overridden by the -L and -l options.  To use
 * system syslog facility run wnsd or wnd with the -S command line option.
 * To do no logging set all the logfiles above to "", the empty string.
 */

#define SWN_PID_FILE	"/var/run/wn.pid"
/*
 * Full path of the file in which you wish the standalone server wnsd
 * to deposit its process id on startup.  Set this to the
 * empty string "" if you want the pid printed to stdout
 * on startup instead of being placed in a file.
 */


#define MAINTAINER	"mailto:root@localhost"
/*
 * Enter "mailto:" followed by the e-mail address of the individual
 * responsible for maintaining your server.  This is a default and
 * can be changed on a per directory basis.  It is used only by WWW
 * clients.
 */


#define MIME_TYPE_FILE	"/etc/mime.types"
#define MAXMIME		(200)
/*
 * This file contains information permitting wndex to translate 
 * ascertain the MIME "Content-type" from the suffix of a file name
 * If this file is not present "wndex -v" will issue a warning
 * but use internal default values.  The file exists so that you
 * can add to it if you wish to add new kinds of documents to your
 * server.  The format of the file is explained in the file.
 * The default version of the file is in /lib/mime.types.
 * The internal defaults are the same as what is currently in this
 * file.
 */


#define RANDOM_DATA_FILE "/dev/urandom"
/*
 * If you don't have a random number generating device
 * create a file with more than 40 bytes of random data,
 * make it readable *only* by root and put its name here.
 * Kernel based devices like /dev/random or /dev/urandom 
 * are better.  For Linux use /dev/urandom.
 */


/*
 ****************************************************************
 * This is the end of the compulsory fill out items (unless you
 * picked OTHER as your OS type above).  If you wish you can change
 * the following defaults; it is a good idea to at least look them
 * over.
 ****************************************************************
 */


#ifndef	TRUE
#define TRUE	(1)
#define FALSE	(0)
#endif

#define MAX_POST_LEN		(10 * 1024 * 1024)
/*
 * This is the maximum size of a file which clients are allowed to send to
 * the server by the POST or PUT methods.  The default value is 10 meg.
 * You may increase this to any value you desire without ill effect on the
 * server.  The only limitation is that due to the limited resources of your
 * system.
 */

#define USE_DEF_CACHE_LIST	(FALSE)
#define DEFAULT_CACHEFILE_LIST "/path/to/cflist.wn"
/*
 * Set this to TRUE if you want to use "default cachefiles".  The default
 * is FALSE.  You must also set the macro
 * DEFAULT_CACHEFILE_LIST to the complete system path to a file
 * containing directory/cachefile pairs.  E.g.,
 *
 * #define     DEFAULT_CACHEFILE_LIST "/path/to/cflist.wn"
 *
 * This file must contain lines of the form 

 * /full/path/2/dir/ <whitespace> /full/path_to/default_cache_file
 *
 * The first entry on each line is a directory which uses a default
 * cachefile.  The second entry on the line is the path to the
 * cachefile you want to use.  This cachefile must be in a
 * directory in the WN data hierarchy.  Comments in this file are
 * anything on a line after the first '#'
 * The first entry may contain the wildcards '*' and '?' which
 * behave in the same way they do as shell metacharacters.  Thus the line
 *
 * /home/<asterisk>/public_html/<asterisk>   /path_to/index.cache
 *  
 *  will cause anything in the directory /home/john/public/ or any of
 *  its subdirectories to use the given default cachefile provided
 *  there is no cachefile in that directory.  Here "<asterisk>" should
 *  be replaced by '*'.  (Puzzle: Why do you think I had to write this
 *  comment like this?) If a cachefile exists in a directory it will
 *  always be used in place of the default.
 */


#define WN_PAM_ENABLED	(TRUE)
/*
 * Set this to TRUE enable PAM based authentication if your system 
 * supports PAM (Plugable Authentication Modules).  This support exists on
 * Linux and Solaris at least.
 */


#if WN_PAM_ENABLED
#define WN_DEFAULT_PAM_SERVICE	"wn_pam"
#define WN_USE_PAM	(TRUE)
#else
#define WN_USE_PAM	(FALSE)
#endif /* WN_PAM_ENABLED */



#define WN_SU_EXEC 	(FALSE)
/*
 * Change this to TRUE and edit the lines below to use suexec.
 * You will also need to edit Makefile or Makefile.dist and
 * set SUEXEC=suexec.  Also you must edit suexec/suexec.h
 * See suexec/INSTALL for more information.  
 */


#if WN_SU_EXEC
#define SUEXEC_HANDLER	"/etc/httpd/suexec"
#define SUEXEC_KEY_FILE "/etc/httpd/suexec.key"
#define RANDOM_DATA_FILE "/dev/urandom"
#define SUEXEC_KEYLEN	(40)
#else
#define WN_popen	popen
#endif
/*
 * SUEXEC_HANDLER is the complete path to the suexec binary.  This
 * binary must have proper ownership and permissions
 * E.g. "chown root.wn suexec" and "chmod 4750 suexec" where
 * "wn" is *group* name of the user under which the server runs.
 * suexec should be executable by root and the server user and 
 * *nobody* else!
 *
 * SUEXEC_KEY_FILE is the complete path to a file the server will create
 * It will be readable *only* by root.  RANDOM_DATA_FILE should be 
 * /dev/random if available, otherwise some secret random data accessible
 * when the server starts.
 */


#define USE_FILE_LOG	(FALSE)
#define USE_SYSLOGD 	(TRUE)
#define USE_NO_LOG	(FALSE)
/* 
 * Set ONE AND ONLY ONE of these three to to TRUE to specify logging
 * in WN's own log file, using the syslogd(8) system logging facility,
 * or to do no logging.
 */

#define VERBOSELOG	(TRUE)
/* By default WN uses the Common Log Format used by NCSA and CERN httpd.
 * Setting this to TRUE will cause additional information to be added to
 * the end of each log line.  In particular the User-Agent and Referrer
 * are logged. N.B.  I have chosen to use the correct spelling of
 * Referrer in the log file.  To enable interoperability and to comply
 * with the CGI spec it is necessary elsewhere to use the incorrect spelling
 * "referer" and the CGI environment variable HTTP_REFERER.
 */


#define	USE_KEEPALIVE	(TRUE)
/* WN supports the processing of multiple requests in a single TCP
 * request.  Some clients have buggy implementations of this so
 * you may not want it.  Setting this to FALSE disables the feature.
 */


#define POST_NO_KEEPALIVE	(TRUE)
/* By default keepalive is disabled for POSTS.  If you want to
 * allow persistent connections for POSTS, set this to FALSE
 */


#define HAS_SNPRINTF	(TRUE)
/* 
 * Set this to false if your system does not have the snprintf() system call.
 */


#define USE_LATIN1	(FALSE)
/* 
 * If you define this to be TRUE then the server will allow *alphabetic* ISO
 * 8859-1 characters in file names which are served.  Normally only ASCII
 * alphanumeric characters are allowed.  The additional allowed
 * characters are those with Hex values from C0 to FF. This includes the
 * (anomolous) division sign.  I recommend that you not do this unless
 * you really know you need it.
 */


#define WN_HOSTNAME	""
/*
 * You may enter your fully qualified host name here.  If the default
 * value of "" is used WN will get the default hostname from your system.
 * If you supply a name it should be a fully qualified domain name.
 * WN will attempt to use the gethostbyname() system call to find the
 * IP address of your server.  
 */


#define SERVER_LOGO	"<hr>\n<address>WN</address>\n"
/*
 * This is displayed with error messages and some other server
 * generated HTML messages.  You may want to customize it.
 */

#define FORBID_CGI	(FALSE)
/*
 * Set this to TRUE if you wish to forbid the use of the use of
 * CGI scripts on your host.  This will enhance security but will,
 * of course, decrease functionality.
 */


#define WN_USERNAME	"http"

#ifdef SOLARIS
#define USERID	(99)
#define GROUPID	(99)
#endif

#ifdef UXPDS
#define USERID	(99)
#define GROUPID	(99)
#endif

#ifndef USERID
#define USERID	(99)
#define GROUPID	(99)
#endif

/*
 * These are the group and user id you want the server to switch to when
 * running inetd or when wnsd is run by root.  They are also used by wnd running
 * under inetd and in this case should agree with the uid you set in 
 * inetd.conf.  I have heard (but not verified) that it is necessary for
 * HPUX users to use a different user id than the one belonging to 'nobody'.
 * If you are using wnd and can't set the uid in your inetd.conf
 * (e.g. Ultrix) be sure to #define SET_UID (uncomment it in this file below).
 */

#define DEFAULT_PORT	(80)
#define DEFAULT_SSL_PORT (443)
/*
 * If you wish to run at a different port than 80, edit this line.
 */

#define NO_DNS_HOSTNAMES	(FALSE)
/*
 * Set this to TRUE if you do not wish the server to look up DNS hostnames
 * from IP addresses and enter them in logfiles.  Instead only the IP
 * address will be in the log file.  This well reduce the load on your
 * server but probably not improve response time since the lookup is usually
 * done after the transaction anyway.
 */

#define WN_IP_ONLY_ACCESS   (FALSE)
/* 
 * Change this to TRUE if you will only use IP addresses in access control
 * files and never use hostnames.  This is more efficient and more 
 * secure.
 */

#define CHECK_DNS_HOSTNAMES	(FALSE)
/*
 * Set this to TRUE if you want to try to check that the client is not 
 * lying about its DNS hostname.  Leave it commented for a slight 
 * efficiency improvement.  The extra check is always done if the 
 * name might be used for access control except when WN_IP_ONLY_ACCESS
 * is defined
 */

#define DEFAULT_URI	"/index.html"

#define INDEXFILE_NAME	"index.html"   /* must be less than 32 chars long */

#define CACHEFNAME	"index.cache"

#define CONTROLFILE_NAME	"index.wn"

#define CONTROLFILE2_NAME	"index"

#define DEFAULT_CONTENT_TYPE	"text/plain"

#define DEFAULT_CHARSET		"iso-8859-1"
/* This is added as a parameter for documents with content type text/something.
 * E.g. an html document will be sent with the header 
 * Content-type=text/html; charset=iso-8859-1
 */

#define BUILTIN_CONTENT_TYPE	"text/html; charset=iso-8859-1"
/* This is the content type used for error messages and builtin
 * search results
 */

#define WN_TEMPDIR		"/tmp"  /* maximum length of this must be < 200 */

#define MAXDEPTH	(10)    /* maximum depth of menus to search */

#define TRANSACTION_TIMEOUT	(600)
				/*
				 * Time in seconds to wait before timeout 
				 * This time is reset if 256 Kb of binary
				 * data or 512 lines of text are sent. For
				 * large binary files this means an average of
				 * about 425 bytes/sec to avoid a timeout.
				 */

/*
 * If you want files ending with a suffixe (e.g. ".shtml") to be 
 * automatically marked to be parsed, set this appropriately. 
 * Don't include the leadding '.' in the extension.
 */

#define PARSE_EXT	"shtml"  /* No files automatically parsed */
/* #define PARSE_EXT	"shtml"*/ /* File extension for parsed HTML  */
/* No '.' for this one! */


/* 
   This is the comma separated list of filename extensions which are
   used to designate that a file is a CGI script.  All extensions start
   with '.'. For example a value might be ".cgi,.php,.tcl".
*/
#define CGI_EXT_LIST		".cgi"  


#define CGI_BIN		"cgi-bin"  /* Name of directory for CGI's */


#define ACCESS_DENIED_URL	""
#define NO_SUCH_FILE_URL	""
#define AUTH_DENIED_FILE	"" 
/*
 * These should all be "" if you don't want to use them.  
 * The first two are URL's, including relative URL's 
 * like /no_such.html for a file in the server data root.
 * the second is a file name relative to the server data root.
 */


/* #define DENYHANDLER "/pub/www/deny-handler" */

/* If defined, DENYHANDLER should be a command that is executed when an
 * "Error 404 - Access denied, or file does not exist" condition
 * is encountered.  The command must act like an nph- CGI program and
 * emit an HTTP status line and full document headers.  A CGI environment
 * is initialized based upon the original (bad) URL.  Comment out this
 * definition to get the standard built-in "Error 404" handling.
 * Thanks to Chip Rosenthal.
 */


#define WN_ENABLE_TRACE		(FALSE)
#define WN_STRICT_SECURITY	(FALSE)

/*
 * Change to TRUE some extra paranoid security at the expense of a little
 * functionality.
 */

#define DIGEST_AUTHENTICATION	(FALSE)
/*
 * Set to TRUE to use digest authentication.
 */


#define USE_VIRTUAL_HOSTS	(FALSE)
#define VIRTUAL_HOSTS_FILE	"/etc/virtual_hosts"
/*
 * Define these appropriately to use a virtual hosts file.  See docs/multi.html
 * for details
 */

#if USE_VIRTUAL_HOSTS
#define DEFAULT_VHOST_FLAG	(0)
#endif


/*
 * The following lines can be uncommented to enable one of the two
 * methods of allowing alternate data hierarchies.  This is the way
 * you permit users to have data hierarchies in their home directories
 * with the URL syntax like http://hostname/~user/.  Read the chapter
 * of the user's guide on this subject (Chapter 11).
 *
 * At most one of USE_TILDE_TABLE and USE_TILDE_USER_PWFILE should be set
 * to TRUE. If both are FALSE (the default) then alternate hierarchies
 * are not allowed.
 *
 * If USE_TILDE_TABLE is TRUE then TILDE_TABLE must be defined to the
 * path of a file containing name:directory pairs.  Then URLs starting
 * with TILDE_USER_STRINGname/foo will be changed to /foo and the root
 * directory will be the directory after the ':' in the table.
 *
 * If USE_TILDE_USER_PWFILE is TRUE then the user's name will be looked
 * up in the password file and the corresponding home directory with
 * the string PUB_HTML appended will be the root directory.  This will
 * fail if the user's uid is less than LEAST_UID.
 */

#define USE_TILDE_TABLE	(FALSE)
#define TILDE_TABLE	"/path/to/rootdir_table"

#define USE_TILDE_PWFILE	(TRUE)

#define TILDE_USER_STRING	"/~"
/*
 * You can also use something like "/homepages/" or "/people/" for this
 * but use "/~"  to make http://hostname/~user/ work.  This appears to
 * be a de facto standard.  This string must start with '/'.
 */


#define PUB_HTML	"/public_html"
#define LEAST_UID	(100)


#define NO_SERVEALL	(FALSE)
/*
 * Set this to TRUE if you want to disable the server's ability
 * to serve documents not listed in an index.cache file.  See the
 * manual section docs/index_desc.html for more details.
 */

/*
 * Uncomment the following if you want the server to attempt to do RFC931
 * (aka RFC1413, IDENT, or TAP) lookups on clients.  This may be good for
 * additional logging information, but should not be trusted for
 * authentication.
 *
 * Because of bugs in many PC TCP/IP stacks that may cause ident
 * connections to time out instead of being refused (certain firewall
 * configurations may cause the same problem) this defaults to off, and
 * the timeout should be kept low.  10 seconds is about as high as I
 * recommend; remember, this timeout will need to be fulfilled on EVERY
 * request from that client, so pages with lots of inline images will
 * become painful.
 *
 * The support code was modified by Christopher Davis <ckd@kei.com> based
 * on the RFC931 lookup code in Wietse Venema's tcp_wrappers 7.2.
 *
 * The support code was further modified by Kenji Rikitake
 * <kenji.rikitake@acm.org> to use T/TCP (RFC1644) if available.
 */
/* #define RFC931_TIMEOUT	(10) */


/*
 * Uncomment the following if you want to disable the T/TCP (Transactional TCP)
 * functionality on WN.  T/TCP functionality is enabled as default
 * in some implementation of UNIXes, such as FreeBSD.  See RFC1644
 * or ttcp(4) man page for the further details.
 *
 * Currently only RFC931 lookups uses T/TCP features (if available).
 */
/* #undef MSG_EOF */


/********************************************************/

#define LOGFACILITY   LOG_DAEMON
#define LOG_PRIORITY    LOG_INFO
#define ERRLOG_PRIORITY    LOG_ERR
/*
 * Change this if you wish to use a local syslog facility.  This only has
 * effect if you are using the "-S" option.  If you use it, select the
 * priority at which you want the messages (LOG_NOTICE or LOG_INFO)?
 *
 */


/********************************************************
 * Edit the lines in this section if you chose OTHER as 
 * your OS type.
 ********************************************************/

/*
 * #define NO_LINGER
 *
 * Comment this out if you have problems with truncated documents being
 * returned to requests from remote hosts.  WN is slightly more efficient
 * with it uncommented.
 *
 */


/*
 * #define BSD_LIKE
 * This should be defined if your system is BSD-like, i.e. tends
 * to use BSD system calls rather than SysV system calls.
 */


/* #define NO_FLOCK */
/*
 * Uncomment this if your system does not have the flock() system call.
 * Doing this means that if more than one client is using your server 
 * at the same time, your logfile might be garbled.  There are no other
 * ill effects.
 *
 */


/*
 * #define SET_UID
 *
 *  Uncomment this if you are using an inetd without the capability 
 *  to set UID on startup (e.g., Ultrix). The user id and group id
 *  under which wnd runs will then be set to the values of USERID and
 *  GROUPID set above.
 */

/*
 * #define NO_SYSLOG
 *
 * Uncomment this if your system does not have the openlog()/syslog()
 * system calls.  Doing this means that you won't be able to have your
 * log entries put in the system log ( the "-S" option to gn).  You
 * can still use the "-L" option to write the entries to a named log file.
 *
 */

#define NO_VOID_PTR	(FALSE)
/*
 *
 * Set this to TRUE if your compiler does not support void pointers.
 *
 */

#define NO_CC_CONST	(FALSE)
/*
 *
 * Uncomment this if your compiler does not support "const" arrays.
 *
 */

#define NEED_PUTENV	(FALSE)
/*
 *
 * Set this to TRUE if your compiler library does not have the function
 * putenv().  
 *
 */

#define NEED_STRFTIME	(FALSE)
/*
 *
 * Set this to TRUE if your compiler library does not have the function
 * strftime()
 *
 */

#define NEED_STRSTR	(FALSE)
/*
 *
 * Set this to TRUE if your compiler library does not have the function
 * strstr()
 *
 */


#define NEED_STRNCASECMP	(FALSE)
/*
 * Set this TRUE if your compiler library does not have the function
 * strncasecmp()
 *
 */

#define NEED_STRCASECMP		(FALSE)
/*
 * Set this TRUE if your compiler library does not have the function
 * strcasecmp()
 *
 */


/*************************************************************
 * Hopefully you shouldn't need to change things below here.
 *************************************************************/



/************************/
#if defined(SUN_OS4)
#define BSD_LIKE
#define NO_CC_CONST	(FALSE)
#endif


/************************/
#if defined(FREE_BSD)
#define BSD_LIKE
#endif


/************************/
#if defined(NET_BSD)
#define BSD_LIKE
#endif


/************************/
#if defined(OPEN_BSD)
#define BSD_LIKE
#endif


/************************/
#if defined(AIX)
#undef BSD_LIKE
#endif


/************************/
#if defined(SOLARIS)
#define WN_SOCKADDR_TYPE	sockaddr
#define bzero(a,b)	memset(a,0,b)
#define bcopy(a,b,n)	memcpy(b,a,n)
#endif


/************************/
#if defined(UXPDS)
#define WN_SOCKADDR_TYPE	sockaddr
#define bzero(a,b)	memset(a,0,b)
#define bcopy(a,b,n)	memcpy(b,a,n)
#endif


/************************/
#if defined(HPUX)
#ifndef _HPUX_SOURCE
#define _HPUX_SOURCE
#endif
#define NO_CC_CONST	(FALSE)
#endif /* HPUX */


/************************/
#if defined(BSDI)
#define BSD_LIKE
#endif


/************************/
#if defined(ULTRIX)
#define BSD_LIKE
#define SET_UID
#endif


/************************/
#if defined(OSF1)
#define BSD_LIKE
#ifndef _BSD
#define _BSD
#endif
#endif    /* OSF1 */


/************************/
#if defined(TRUE64)
#define BSD_LIKE
#ifndef _BSD
#define _BSD
#endif
#endif    /* TRUE64 */


/************************/
#if defined(DYNIX)
#define BSD_LIKE
#undef BSD_LIKE
#define NO_SETSID	(TRUE)
#define bzero(a,b)      memset(a,0,b)
#define bcopy(a,b,n)	memcpy(b,a,n)
#endif


/************************/
#if defined(NEXT)
#define BSD_LIKE
#define WN_SOCKADDR_TYPE	sockaddr
#undef NEED_PUTENV
#define NEED_PUTENV	(TRUE)
#undef NEED_STRFTIME
#define NEED_STRFTIME	(TRUE)
#define NEED_DIR_H
#define NO_SETSID	(TRUE)

typedef	int	pid_t;

#ifndef S_ISDIR
#define S_ISDIR(m)      (((m)&(S_IFMT)) == (S_IFDIR))
#endif

#ifndef S_ISREG
#define S_ISREG(m)	(((m) & (_S_IFMT)) == (_S_IFREG))
#endif /*S_ISREG*/

#endif /* NEXT */


/************************/
#if defined(SCO)
#undef BSD_LIKE
#define NEED_INITGROUPS	(TRUE)
#endif

/************************/
#if defined(CONVEX_OS)
#undef BSD_LIKE
#endif

/************************/
#if defined(LINUX)
#define WN_SOCKADDR_TYPE	sockaddr
#define _WN_SIGCHLD     SIGCHLD
#endif


/************************/
#if defined(PYRAMID)
#undef NEED_PUTENV
#define NEED_PUTENV	(TRUE)
#undef NEED_STRFTIME
#define NEED_STRFTIME	(TRUE)
#define POSIX_SIGNALS
#endif


/************************/
#if defined(AUX)
#undef BSD_LIKE

#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE
#endif
#endif /* AUX */


/************************/
#if defined(SGI)
#define _WN_SIGCHLD	SIGCHLD
#endif


/************************/
#if defined(SVR4)
#define NEED_STRNCASECMP
#define POSIX_SIGNALS
#endif

/************************/
#if defined(SINIX)
#define NEED_STRNCASECMP
#define POSIX_SIGNALS
#define NEED_STRCASECMP
#define bzero(a,b)      memset(a,0,b)
#define bcopy(a,b,n)    memcpy(b,a,n)
#endif

/************************/
#if defined(UNIXWARE)
#undef BSD_LIKE
#define bzero(a,b)	memset(a,0,b)
#define bcopy(a,b,n)	memcpy(b,a,n)
#define NEED_STRNCASECMP
#define NEED_STRCASECMP
#endif


/************************/
#if defined(ISC)
#undef BSD_LIKE
#define NO_SETSID	(TRUE)
#define bzero(a,b)	memset(a,0,b)
#define bcopy(a,b,n)	memcpy(b,a,n)
#endif


/************************/
#if defined(RISCOS)
/*
 * This is for RISC/os 4.01 (old); more recent versions may not have
 * as much braindamage
 */
#define BSD_LIKE
#undef NEED_PUTENV
#define NEED_PUTENV	(TRUE)
#undef NEED_STRFTIME
#define NEED_STRFTIME	(TRUE)
#undef NEED_STRSTR
#define NEED_STRSTR	(TRUE)
extern char *strstr ();
#undef NO_SETSID
#define NO_SETSID	(TRUE)
#define NO_UNISTD_H
#define NEED_DIR_H
typedef	int	pid_t;
#ifndef S_ISDIR
#define S_ISDIR(m)      (((m)&(S_IFMT)) == (S_IFDIR))
#endif

#ifndef S_ISREG
#define S_ISREG(m)	(((m) & (S_IFMT)) == (S_IFREG))
#endif

#ifndef S_IROTH
#define S_IROTH 0000004
#endif
#ifndef WEXITSTATUS
#define WEXITSTATUS(x)  (((union wait*)&(x))->w_retcode)
#endif
#endif /* RISCOS */


/************************/

/* This stuff is for everyone */

#if HAS_SNPRINTF
#define Snprintf1	snprintf
#define Snprintf2	snprintf
#define Snprintf3	snprintf
#define Snprintf4	snprintf
#define Snprintf5	snprintf
#else
#define Snprintf1(a,b,c,x1)			sprintf(a,c,x1)
#define Snprintf2(a,b,c,x1,x2)			sprintf(a,c,x1,x2)
#define Snprintf3(a,b,c,x1,x2,x3)		sprintf(a,c,x1,x2,x3)
#define Snprintf4(a,b,c,x1,x2,x3,x4)		sprintf(a,c,x1,x2,x3,x4)
#define Snprintf5(a,b,c,x1,x2,x3,x4,x5)		sprintf(a,c,x1,x2,x3,x4,x5)
#endif

#ifndef _WN_SIGCHLD
#ifdef	BSD_LIKE
#define _WN_SIGCHLD	SIGCHLD
#else
#define _WN_SIGCHLD	SIGCLD
#endif /* BSD_LIKE */
#endif /* _WN_SIGCHLD */

#if NO_VOID_PTR
#define	void	int
#endif

#if NO_CC_CONST
#define WN_CONST
#else
#define WN_CONST	const
#endif

#ifndef NO_SETSID
#define NO_SETSID	(FALSE)
#endif

#ifndef WN_SOCKADDR_TYPE
#define WN_SOCKADDR_TYPE	sockaddr_in
#endif

