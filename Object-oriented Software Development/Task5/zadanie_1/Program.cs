// See https://aka.ms/new-console-template for more information
using System.Net.Mail;
using System.Net.Mime;

namespace Zadanie1 // Note: actual namespace depends on the project name.
{
    public class SmtpFacade {

        private SmtpClient _client;

        public SmtpFacade(string host, int port){
            _client = new SmtpClient(host, port);
        }

        public void Send(
            string From, 
            string To, 
            string Subject, 
            string Body, 
            Stream Attachment, 
            string AttachmentMimeType
        ){
            if(this._client == null)
            {
                throw new InvalidOperationException("Can't Send when cluent is null!");
            }
            MailMessage mailMessage = new MailMessage(From, To, Subject, Body);
            if (Attachment != null && AttachmentMimeType != null)
            {
                mailMessage.Attachments.Add(
                    new Attachment(Attachment, new ContentType(AttachmentMimeType))
                );
            }
            this._client.Send(mailMessage);
        }
    }

    internal class Program
    {
        static void Main(string[] args)
        {
            SmtpFacade smtpFacade = new SmtpFacade("0.0.0.0", 23);
        }
    }
}
