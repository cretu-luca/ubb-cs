SELECT 
    session_id,
    login_name,
    host_name,
    program_name,
    login_time,
    status,
    last_request_start_time
FROM sys.dm_exec_sessions
WHERE database_id = DB_ID('CityPlanning')
ORDER BY login_time DESC;

KILL id
