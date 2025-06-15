using System.ComponentModel.DataAnnotations;

namespace asp_dotnet.Model
{
    public class Hotel
    {
        [Key]
        public int hotelId { get; set; }
        public String? hotelName { get; set; }
        public String? hotelDate { get; set; }
        public String? city { get; set; }
        public int availableRooms { get; set; }
    }
}