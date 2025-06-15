using System.ComponentModel.DataAnnotations;

namespace asp_dotnet.Model
{
    public class Reservation
    {
        [Key]
        public int reservationId { get; set; }
        public String? person { get; set; }
        public String? Type { get; set; }
        public int idReservedResource { get; set; }
    }
}