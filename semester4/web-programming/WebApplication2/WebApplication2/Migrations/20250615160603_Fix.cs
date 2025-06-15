using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebApplication2.Migrations
{
    /// <inheritdoc />
    public partial class Fix : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Persons_Courses_ProfessorId",
                table: "Persons");

            migrationBuilder.DropColumn(
                name: "CourseName",
                table: "Persons");

            migrationBuilder.RenameColumn(
                name: "ProfessorId",
                table: "Persons",
                newName: "CourseId");

            migrationBuilder.RenameColumn(
                name: "Participants",
                table: "Persons",
                newName: "Role");

            migrationBuilder.RenameColumn(
                name: "Grades",
                table: "Persons",
                newName: "Name");

            migrationBuilder.RenameIndex(
                name: "IX_Persons_ProfessorId",
                table: "Persons",
                newName: "IX_Persons_CourseId");

            migrationBuilder.RenameColumn(
                name: "Role",
                table: "Courses",
                newName: "Participants");

            migrationBuilder.RenameColumn(
                name: "Name",
                table: "Courses",
                newName: "Grades");

            migrationBuilder.AddColumn<string>(
                name: "CourseName",
                table: "Courses",
                type: "longtext",
                nullable: false)
                .Annotation("MySql:CharSet", "utf8mb4");

            migrationBuilder.AddColumn<int>(
                name: "ProfessorId",
                table: "Courses",
                type: "int",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.CreateIndex(
                name: "IX_Courses_ProfessorId",
                table: "Courses",
                column: "ProfessorId");

            migrationBuilder.AddForeignKey(
                name: "FK_Courses_Persons_ProfessorId",
                table: "Courses",
                column: "ProfessorId",
                principalTable: "Persons",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);

            migrationBuilder.AddForeignKey(
                name: "FK_Persons_Courses_CourseId",
                table: "Persons",
                column: "CourseId",
                principalTable: "Courses",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Courses_Persons_ProfessorId",
                table: "Courses");

            migrationBuilder.DropForeignKey(
                name: "FK_Persons_Courses_CourseId",
                table: "Persons");

            migrationBuilder.DropIndex(
                name: "IX_Courses_ProfessorId",
                table: "Courses");

            migrationBuilder.DropColumn(
                name: "CourseName",
                table: "Courses");

            migrationBuilder.DropColumn(
                name: "ProfessorId",
                table: "Courses");

            migrationBuilder.RenameColumn(
                name: "Role",
                table: "Persons",
                newName: "Participants");

            migrationBuilder.RenameColumn(
                name: "Name",
                table: "Persons",
                newName: "Grades");

            migrationBuilder.RenameColumn(
                name: "CourseId",
                table: "Persons",
                newName: "ProfessorId");

            migrationBuilder.RenameIndex(
                name: "IX_Persons_CourseId",
                table: "Persons",
                newName: "IX_Persons_ProfessorId");

            migrationBuilder.RenameColumn(
                name: "Participants",
                table: "Courses",
                newName: "Role");

            migrationBuilder.RenameColumn(
                name: "Grades",
                table: "Courses",
                newName: "Name");

            migrationBuilder.AddColumn<string>(
                name: "CourseName",
                table: "Persons",
                type: "longtext",
                nullable: false)
                .Annotation("MySql:CharSet", "utf8mb4");

            migrationBuilder.AddForeignKey(
                name: "FK_Persons_Courses_ProfessorId",
                table: "Persons",
                column: "ProfessorId",
                principalTable: "Courses",
                principalColumn: "Id",
                onDelete: ReferentialAction.Cascade);
        }
    }
}
