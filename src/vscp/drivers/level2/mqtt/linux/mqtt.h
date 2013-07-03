// mqtt.h: interface for the mqtt class.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 2 of the License, or (at your option) any later version.
// 
// This file is part of the VSCP (http://www.vscp.org) 
//
// Copyright (C) 2000-2013 Ake Hedman, 
// Grodans Paradis AB, <akhe@grodansparadis.com>
// 
// This file is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this file see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//


#if !defined(AFX_VSCPLOG_H__6F5CD90E_ACF7_459A_9ACB_849A57595639__INCLUDED_)
#define AFX_VSCPLOG_H__6F5CD90E_ACF7_459A_9ACB_849A57595639__INCLUDED_

#ifdef WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef WIN32

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#else

#define _POSIX
#include <unistd.h>
#include <pthread.h>
#include <syslog.h>

#endif

#include <mosquittopp.h>

#include <wx/file.h>
#include <wx/wfstream.h>

#include "../../../../common/canal.h"
#include "../../../../common/vscp.h"
#include "../../../../common/canal_macro.h"
#include "../../../../../common/dllist.h"
#include "../../../../common/vscptcpif.h"
#include "../../../../common/guid.h"



#define VSCP_LEVEL2_DLL_MQTT_OBJ_MUTEX "___VSCP__DLL_L2MQTT_OBJ_MUTEX____"

#define VSCP_MQTT_LIST_MAX_MSG		2048


// Forward declarations
class CWrkThread;
class VscpTcpIf;
class wxFile;

// Subscribe base class

class mqtt_subscribe : public mosqpp::mosquittopp {
public:
    mqtt_subscribe(const wxString& usernameLocal,
            const wxString& passwordLocal,
            const wxString& hostLocal = _("localhost"),
            const int portLocal = 9598,
            const wxString& topic = _("vscp"),
            const wxString& hostRemote = _("localhost"),
            int portRemote = 1883,
            int keepalive = 60);
    ~mqtt_subscribe();

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);

    /*!
    VSCP daemon address
     */
    wxString m_hostLocal;

    /*!
        VSCP daemon port
     */
    int m_portLocal;

    /*!
        User name for VSCP daemon
     */
    wxString m_usernameLocal;

    /*!
        Password for VSCP daemon
     */
    wxString m_passwordLocal;

    /*!
        Subscribe or Publish topic.
     */
    wxString m_topic;
    
    /*!
        MQTT host (broker)
     */
    wxString m_hostMQTT;
    
    /*!
        MQTT port
    */       
	int m_portMQTT;
                
    /*!
        Keepalive value
    */
	int m_keepalive;
    
    /// VSCP server interface
    VscpTcpIf m_srv;
};

// Publish base class

class mqtt_publish : public mosqpp::mosquittopp {
public:
    mqtt_publish(const wxString& usernameLocal,
            const wxString& passwordLocal,
            const wxString& hostLocal = _("localhost"),
            const int portLocal = 9598,
            const wxString& topic = _("vscp"),
            const wxString& hostRemote = _("localhost"),
            int portRemote = 1883,
            int keepalive = 60);
    ~mqtt_publish();

    void on_connect(int rc);
    void on_message(const struct mosquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos);

    /*!
    VSCP daemon address
     */
    wxString m_hostLocal;

    /*!
        VSCP daemon port
     */
    int m_portLocal;

    /*!
        User name for VSCP daemon
     */
    wxString m_usernameLocal;

    /*!
        Password for VSCP daemon
     */
    wxString m_passwordLocal;

    /*!
        Subscribe or Publish topic.
     */
    wxString m_topic;
    
    /*!
        MQTT host (broker)
     */
    wxString m_hostMQTT;
    
    /*!
        MQTT port
    */       
	int m_portMQTT;
                
    /*!
        Keepalive value
    */
	int m_keepalive;
};

class Cmqtt {
public:

    /// Constructor
    Cmqtt();

    /// Destructor
    virtual ~Cmqtt();

    /*! 
        Open
        @return True on success.
     */
    bool open(const char *pUsername,
            const char *pPassword,
            const char *pHost,
            short port,
            const char *pPrefix,
            const char *pConfig);

    /*!
        Flush and close the log file
     */
    void close(void);



public:

    /// Run flag
    bool m_bQuit;
    
    /// True if we should subscribe. False if we should publish)
    bool bSubscribe;

    /// Server supplied username
    wxString m_username;

    /// Server supplied password
    wxString m_password;

    /// server supplied prefix
    wxString m_prefix;

    /// server supplied host
    wxString m_host;

    /// Server supplied port
    short m_port;

    /*!
        Subscribe or Publish topic.
     */
    wxString m_topic;
    
    /*!
        MQTT host (broker)
     */
    wxString m_hostMQTT;
    
    /*!
        MQTT port
    */       
	int m_portMQTT;
    
    /*!
        MQTT username (broker)
     */
    wxString m_usernameMQTT;
    
    /*!
        MQTT password (broker)
     */
    wxString m_passwordMQTT;
                
    /*!
        Keepalive value
    */
	int m_keepalive;

    /// Filter
    vscpEventFilter m_vscpfilter;

    /// Pointer to worker thread
    CWrkThread *m_pthreadWork;

    /// VSCP server interface
    VscpTcpIf m_srv;

};

///////////////////////////////////////////////////////////////////////////////
//				                Worker Treads
///////////////////////////////////////////////////////////////////////////////

class CWrkThread : public wxThread {
public:

    /// Constructor
    CWrkThread();

    /// Destructor
    ~CWrkThread();

    /*!
        Thread code entry point
     */
    virtual void *Entry();

    /*! 
        called when the thread exits - whether it terminates normally or is
        stopped with Delete() (but not when it is Kill()ed!)
     */
    virtual void OnExit();

    /// VSCP server interface
    VscpTcpIf m_srv;

    /// Sensor object
    Cmqtt *m_pObj;

};

class CWriteSocketCanTread : public wxThread {
public:

    /// Constructor
    CWriteSocketCanTread();

    /// Destructor
    ~CWriteSocketCanTread();

    /*!
        Thread code entry point
     */
    virtual void *Entry();

    /*! 
        called when the thread exits - whether it terminates normally or is
        stopped with Delete() (but not when it is Kill()ed!)
     */
    virtual void OnExit();

    /// VSCP server interface
    VscpTcpIf m_srv;

    /// Sensor object
    Cmqtt *m_pObj;

};


#endif // !defined(AFX_VSCPLOG_H__6F5CD90E_ACF7_459A_9ACB_849A57595639__INCLUDED_)