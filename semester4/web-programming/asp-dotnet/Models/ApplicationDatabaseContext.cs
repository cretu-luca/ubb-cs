using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using asp_dotnet.Models;

namespace asp_dotnet.Models;

public class ApplicationDatabaseContext : DbContext
{
    public ApplicationDatabaseContext(DbContextOptions<ApplicationDatabaseContext> options)
        : base(options)
    {
    }

    public DbSet<Recipe> Recipe { get; set; } = null!;
    public DbSet<Ingredient> Ingredient { get; set; } = null!;
    public DbSet<User> Users { get; set; } = null!;
}