namespace WebApplication5.Model;

public class Reservation
{
    public int Id { get; set; }
    public int UserId { get; set; }
    public int RoomId { get; set; }
    public DateTime CheckInDate { get; set; }
    public DateTime CheckOutDate { get; set; }
    public int NumberOfGuests { get; set; }
    public int TotalPrice { get; set; }
}