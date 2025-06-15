using asp_dotnet.Model;
using asp_dotnet.Repository;

namespace asp_dotnet.Repository
{
    public class ReservationRepository : BaseRepository<Reservation>, IReservationRepository
    {
        public ReservationRepository(ApplicationDatabaseContext context) : base(context)
        {
        }
    }
}