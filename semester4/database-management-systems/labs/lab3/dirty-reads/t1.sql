USE CityPlanning

BEGIN TRAN
    UPDATE Project
    SET ProjectName = 'Dirty read'
    WHERE ProjectID = 6

    WAITFOR DELAY '00:00:5'

    ROLLBACK TRAN
