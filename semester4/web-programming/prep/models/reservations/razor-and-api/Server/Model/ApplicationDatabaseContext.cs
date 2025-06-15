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

    public DbSet<User> Users { get; set; } = null!;
    public DbSet<Hotel> Hotels { get; set; } = null!;
    public DbSet<Flight> Flights { get; set; } = null!;
    public DbSet<Reservation> Reservations { get; set; } = null!;
}