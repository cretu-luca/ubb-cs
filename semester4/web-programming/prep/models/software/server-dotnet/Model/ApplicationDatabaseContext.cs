using Microsoft.EntityFrameworkCore;
using System.Collections.Generic;
using asp_dotnet.Model;

namespace asp_dotnet.Model;

public class ApplicationDatabaseContext : DbContext
{
    public ApplicationDatabaseContext(DbContextOptions<ApplicationDatabaseContext> options)
        : base(options)
    {
    }

    public DbSet<SoftwareDeveloper> SoftwareDeveloper { get; set; } = null!;
    public DbSet<Project> Project { get; set; } = null!;
}