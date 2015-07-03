using System;
using System.IO;
using System.Security;
using System.Security.Cryptography;
using System.Runtime.InteropServices;
using System.Text;

namespace LyncWpfApp
{
    /// <summary>
    /// 对本地xml文件进行加密、解密
    /// </summary>
    public class EncryptDecrypt
    {
        //  Call this function to remove the key from memory after use for security
        [DllImport("KERNEL32.DLL", EntryPoint = "RtlZeroMemory")]
        static extern bool ZeroMemory(IntPtr Destination, int Length);
        //默认密钥向量     
        private static byte[] Keys = { 0x11, 0x33, 0x56, 0x78, 0x92, 0xAB, 0xCD, 0xEF }; 
        // Function to Generate a 64 bits Key.
        static string GenerateKey()
        {
            // Use the Automatically generated key for Encryption. 
            return ASCIIEncoding.UTF8.GetString(Keys);
        }

        static void EncryptFile(string sInputFilename,string sOutputFilename,string sKey)
        {
            FileStream fsInput = new FileStream(sInputFilename,FileMode.Open,FileAccess.ReadWrite);

            FileStream fsEncrypted = new FileStream(sOutputFilename,FileMode.Create,FileAccess.ReadWrite);
            DESCryptoServiceProvider DES = new DESCryptoServiceProvider();
            DES.Key = ASCIIEncoding.ASCII.GetBytes(sKey);
            DES.IV = ASCIIEncoding.ASCII.GetBytes(sKey);
            ICryptoTransform desencrypt = DES.CreateEncryptor();
            CryptoStream cryptostream = new CryptoStream(fsEncrypted,desencrypt,CryptoStreamMode.Write);

            byte[] bytearrayinput = new byte[fsInput.Length];
            fsInput.Read(bytearrayinput, 0, bytearrayinput.Length);
            cryptostream.Write(bytearrayinput, 0, bytearrayinput.Length);
            cryptostream.Close();
            fsInput.Close();
            fsEncrypted.Close();
        }

        static void DecryptFile(string sInputFilename,
           string sOutputFilename,
           string sKey)
        {
            DESCryptoServiceProvider DES = new DESCryptoServiceProvider();
            //A 64 bit key and IV is required for this provider.
            //Set secret key For DES algorithm.
            DES.Key = ASCIIEncoding.ASCII.GetBytes(sKey);
            //Set initialization vector.
            DES.IV = ASCIIEncoding.ASCII.GetBytes(sKey);

            //Create a file stream to read the encrypted file back.
            FileStream fsread = new FileStream(sInputFilename,
               FileMode.Open,
               FileAccess.Read);
            //Create a DES decryptor from the DES instance.
            ICryptoTransform desdecrypt = DES.CreateDecryptor();
            //Create crypto stream set to read and do a 
            //DES decryption transform on incoming bytes.
            CryptoStream cryptostreamDecr = new CryptoStream(fsread,
               desdecrypt,
               CryptoStreamMode.Read);
            //Print the contents of the decrypted file.
            StreamWriter fsDecrypted = new StreamWriter(sOutputFilename);
            fsDecrypted.Write(new StreamReader(cryptostreamDecr).ReadToEnd());
            fsDecrypted.Flush();
            fsDecrypted.Close();
            fsread.Close();
            fsread.Dispose();
        }

        public static void DecryptUserConfigFile()
        {
            // Must be 64 bits, 8 bytes.
            // Distribute this key to the user who will decrypt this file.
            string sSecretKey;

            // Get the Key for the file to Encrypt.
            sSecretKey = GenerateKey();

            // For additional security Pin the key.
            GCHandle gch = GCHandle.Alloc(sSecretKey, GCHandleType.Pinned);

            // Decrypt the file.
            DecryptFile(System.Windows.Forms.Application.StartupPath + "\\UserConfig.xml",
               System.Windows.Forms.Application.StartupPath + "\\UserConfigBak.xml",
               sSecretKey);

            // Remove the Key from memory. 
            ZeroMemory(gch.AddrOfPinnedObject(), sSecretKey.Length * 2);
            gch.Free();
        }
        public static void EncryptUserConfigFile()
        {
            // Must be 64 bits, 8 bytes.
            // Distribute this key to the user who will decrypt this file.
            string sSecretKey;

            // Get the Key for the file to Encrypt.
            sSecretKey = GenerateKey();

            // For additional security Pin the key.
            GCHandle gch = GCHandle.Alloc(sSecretKey, GCHandleType.Pinned);

            // Encrypt the file.        
            EncryptFile(System.Windows.Forms.Application.StartupPath + "\\UserConfigbak.xml",
               System.Windows.Forms.Application.StartupPath + "\\UserConfig.xml",
               sSecretKey);

            // Remove the Key from memory. 
            ZeroMemory(gch.AddrOfPinnedObject(), sSecretKey.Length * 2);
            gch.Free();
        }
    }
}