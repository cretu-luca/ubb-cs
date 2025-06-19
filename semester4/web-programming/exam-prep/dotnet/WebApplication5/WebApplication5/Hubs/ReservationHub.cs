using Microsoft.AspNetCore.SignalR;

namespace WebApplication5.Hubs
{
    public class ReservationHub : Hub
    {
        public async Task SendReservationNotification(string message)
        {
            await Clients.Others.SendAsync("ReceiveNotification", message);
        }
    }
} 