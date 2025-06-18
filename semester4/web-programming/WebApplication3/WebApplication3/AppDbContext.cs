using WebApplication3.Models;
using Microsoft.EntityFrameworkCore;

namespace WebApplication3;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options)
    {
    }
    
    public DbSet<SoftwareDeveloper> Developers { get; set; }
    public DbSet<Project> Projects { get; set; }
    
    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Project>()
            .HasOne<SoftwareDeveloper>()
            .WithMany()
            .HasForeignKey(p => p.ProjectManagerId);
    }
}