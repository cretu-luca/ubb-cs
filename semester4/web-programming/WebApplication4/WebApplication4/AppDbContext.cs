using Microsoft.EntityFrameworkCore;
using WebApplication4.Models;

namespace WebApplication4;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options)
        : base(options)
    {
    }
    
    public DbSet<Flight> Flights { get; set; }
    public DbSet<Reservation> Reservations { get; set; }
    public DbSet<Hotel> Hotels { get; set; }
    
    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        
    }
}