USE CityPlanning

SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE

BEGIN TRAN
    SELECT * FROM dbo.Project

    WAITFOR DELAY '00:00:05'

    SELECT * FROM dbo.Project
COMMIT TRAN
