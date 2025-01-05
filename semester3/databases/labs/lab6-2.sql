BEGIN
    DELETE FROM TestRunViews
    DELETE FROM TestRunTables
    DELETE FROM TestRuns
    DELETE FROM TestViews
    DELETE FROM TestTables
    DELETE FROM Tests
    DELETE FROM Tables
    DELETE FROM Views

    INSERT INTO Tables (Name) VALUES
        ('Budget'),
        ('City'),
        ('Department');

    INSERT INTO Views (Name) VALUES
        ('CityPopulation'),
        ('CityDepartments'),
        ('CityDepartmentStats');

    INSERT INTO Tests (Name) VALUES
        ('delete_table_100'),
        ('insert_table_100'),
        ('select_view');

    DECLARE @BudgetID INT = (SELECT TableID FROM Tables WHERE Name = 'Budget');
    DECLARE @CityID INT = (SELECT TableID FROM Tables WHERE Name = 'City');
    DECLARE @DeptID INT = (SELECT TableID FROM Tables WHERE Name = 'Department');
    DECLARE @DeleteTestID INT = (SELECT TestID FROM Tests WHERE Name = 'delete_table_100');
    DECLARE @InsertTestID INT = (SELECT TestID FROM Tests WHERE Name = 'insert_table_100');
    DECLARE @SelectTestID INT = (SELECT TestID FROM Tests WHERE Name = 'select_view');

    INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) VALUES
        (@DeleteTestID, @BudgetID, 100, 1),
        (@DeleteTestID, @CityID, 100, 2),
        (@DeleteTestID, @DeptID, 100, 3),
        (@InsertTestID, @BudgetID, 100, 1),
        (@InsertTestID, @CityID, 100, 2),
        (@InsertTestID, @DeptID, 100, 3);

    INSERT INTO TestViews (TestID, ViewID)
    SELECT @SelectTestID, ViewID FROM Views;
END;

CREATE OR ALTER PROCEDURE runTest
    @TestName VARCHAR(50),
    @TableName VARCHAR(50)
AS
BEGIN
    SET NOCOUNT ON;
    DECLARE @TestID INT = (SELECT TestID FROM Tests WHERE Name = @TestName);
    IF @TestID IS NULL RETURN;

    DECLARE @TestRunID INT;
    DECLARE @StartTime DATETIME = GETDATE();

    INSERT INTO TestRuns (Description, StartAt, EndAt)
    VALUES (@TestName, @StartTime, @StartTime);
    SET @TestRunID = SCOPE_IDENTITY();

    IF @TestName = 'delete_table_100'
    BEGIN
        DECLARE @DeleteStart DATETIME = GETDATE();

        IF @TableName = 'Department'
            DELETE FROM Department;
        ELSE IF @TableName = 'City'
            DELETE FROM City;
        ELSE IF @TableName = 'Budget'
            DELETE FROM Budget;

        INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
        SELECT
            @TestRunID,
            TableID,
            @DeleteStart,
            GETDATE()
        FROM TestTables
        WHERE TestID = @TestID;
    END

    IF @TestName = 'insert_table_100'
    BEGIN
        DECLARE @InsertStart DATETIME = GETDATE();
        DECLARE @RowCount INT;

        SELECT @RowCount = NoOfRows
        FROM TestTables tt
        JOIN Tables t ON tt.TableID = t.TableID
        WHERE t.Name = 'Budget' AND tt.TestID = @TestID;

        IF @TableName = 'Budget'
            EXEC InsertTestBudget @RowCount;
        ELSE IF @TableName = 'City'
            EXEC InsertTestCity @RowCount;
        ELSE IF @TableName = 'Department'
            EXEC InsertTestDepartment @RowCount;

        INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt)
        SELECT
            @TestRunID,
            TableID,
            @InsertStart,
            GETDATE()
        FROM TestTables
        WHERE TestID = @TestID;
    END

    IF @TestName = 'select_view'
    BEGIN
        DECLARE @ViewStart DATETIME = GETDATE();

        INSERT INTO TestRunViews (TestRunID, ViewID, StartAt, EndAt)
        SELECT
            @TestRunID,
            ViewID,
            @ViewStart,
            @ViewStart
        FROM TestViews
        WHERE TestID = @TestID;

        IF @TableName = 'CityPopulation'
            SELECT * FROM CityPopulation;
        ELSE IF @TableName = 'CityDepartments'
            SELECT * FROM CityDepartments;
        ELSE IF @TableName = 'CityDepartmentStats'
            SELECT * FROM CityDepartmentStats;
    END

    UPDATE TestRuns
    SET EndAt = GETDATE()
    WHERE TestRunID = @TestRunID;
END;

EXEC runTest 'delete_table_100', 'Department';
EXEC runTest 'delete_table_100', 'City';
EXEC runTest 'delete_table_100', 'Budget';

SELECT 'Budget' as TableName, COUNT(*) as Count FROM Budget
UNION ALL
SELECT 'City', COUNT(*) FROM City
UNION ALL
SELECT 'Department', COUNT(*) FROM Department;

EXEC runTest 'insert_table_100', 'Budget';
EXEC runTest 'insert_table_100', 'City';
EXEC runTest 'insert_table_100', 'Department';

SELECT 'Budget' as TableName, COUNT(*) as Count FROM Budget
UNION ALL
SELECT 'City', COUNT(*) FROM City
UNION ALL
SELECT 'Department', COUNT(*) FROM Department;

EXEC runTest 'select_view', 'CityPopulation';
EXEC runTest 'select_view', 'CityDepartments';
EXEC runTest 'select_view', 'CityDepartmentStats';

SELECT * FROM CityPopulation;
SELECT * FROM CityDepartments;
SELECT * FROM CityDepartmentStats;

SELECT
    tr.Description as TestName,
    tr.StartAt,
    tr.EndAt,
    DATEDIFF(millisecond, tr.StartAt, tr.EndAt) as Duration_ms
FROM TestRuns tr
ORDER BY tr.TestRunID;

SELECT * FROM Tests;
SELECT * FROM Tables;
SELECT * FROM Views;

SELECT * FROM TestTables;
SELECT * FROM TestViews;

SELECT * FROM TestRuns;
SELECT * FROM TestRunTables;
SELECT * FROM TestRunViews;
