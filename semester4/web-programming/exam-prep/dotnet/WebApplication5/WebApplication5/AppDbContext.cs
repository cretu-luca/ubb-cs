using Microsoft.EntityFrameworkCore;
using WebApplication5.Model;

namespace WebApplication5;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options) : base(options) { }
    
    public DbSet<Reservation> Reservations { get; set; }
    public DbSet<HotelRoom> HotelRooms { get; set; }
    public DbSet<User> Users { get; set; }

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        
    }
}