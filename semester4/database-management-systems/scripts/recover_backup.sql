USE master;

RESTORE DATABASE CityPlanning FROM DISK = 'C:\Backups\CityPlanning_Full_Backup.bak'
WITH REPLACE;
