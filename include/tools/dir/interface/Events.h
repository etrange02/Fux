#ifndef TOOLS_DIR_FILE_EVENTS_H_INCLUDED
#define TOOLS_DIR_FILE_EVENTS_H_INCLUDED

#define EVT_TOOLS_DIR_FILE_CLOSE(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_TOOLS_DIR_FILE_CLOSE, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_TOOLS_DIR_FILE_RANGE(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_TOOLS_DIR_FILE_RANGE, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_TOOLS_DIR_FILE_UPDATE(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_TOOLS_DIR_FILE_UPDATE, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#define EVT_TOOLS_DIR_FILE_ASK_REC_QUESTION(fn)\
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_TOOLS_DIR_FILE_ASK_REC_QUESTION, wxID_ANY, wxID_ANY,\
    (wxObjectEventFunction)(wxEventFunction) wxStaticCastEvent( wxCommandEventFunction, &fn ), \
    (wxObject *) NULL ),

#endif // TOOLS_DIR_FILE_EVENTS_H_INCLUDED
