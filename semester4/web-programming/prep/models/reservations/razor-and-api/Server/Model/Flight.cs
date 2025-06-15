using System.ComponentModel.DataAnnotations;

namespace asp_dotnet.Model
{
    public class Flight
    {
        [Key]
        public int FlightId { get; set; }
        public String? flightDate { get; set; }
        public String? destinationCity { get; set; }
        public int availableSeats { get; set; }
    }
}