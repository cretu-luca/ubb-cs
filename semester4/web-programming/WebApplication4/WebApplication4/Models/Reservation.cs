namespace WebApplication4.Models;

public class Reservation
{
    public int Id { get; set; }
    public String Person { get; set; }
    public String Type { get; set; }
    public int ReservedResourceId { get; set; }
}