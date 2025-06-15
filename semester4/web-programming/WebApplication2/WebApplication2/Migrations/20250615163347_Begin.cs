using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace WebApplication2.Migrations
{
    /// <inheritdoc />
    public partial class Begin : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Persons_Courses_CourseId",
                table: "Persons");

            migrationBuilder.DropIndex(
                name: "IX_Persons_CourseId",
                table: "Persons");

            migrationBuilder.DropColumn(
                name: "CourseId",
                table: "Persons");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "CourseId",
                table: "Persons",
                type: "int",
                nullable: true);

            migrationBuilder.CreateIndex(
                name: "IX_Persons_CourseId",
                table: "Persons",
                column: "CourseId");

            migrationBuilder.AddForeignKey(
                name: "FK_Persons_Courses_CourseId",
                table: "Persons",
                column: "CourseId",
                principalTable: "Courses",
                principalColumn: "Id");
        }
    }
}
