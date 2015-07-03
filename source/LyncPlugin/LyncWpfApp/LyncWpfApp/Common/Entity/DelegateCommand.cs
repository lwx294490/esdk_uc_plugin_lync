using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;

namespace LyncWpfApp
{
    public class DelegateCommand : ICommand
    {
        private Action _executeMethod;
        private Predicate<object> _canExecuteMethod;

        #region ICommand Members

        public DelegateCommand(Action executeMethod, Predicate<object> canExecuteMethod = null)
        {
            _executeMethod = executeMethod;
            _canExecuteMethod = canExecuteMethod;
        }

        public bool CanExecute(object parameter)
        {
            if (_canExecuteMethod == null)
                return true;

            return _canExecuteMethod(parameter);
        }

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        public void Execute(object parameter)
        {
            _executeMethod();
        }

        #endregion
    }

    public class DelegateCommand<T> : ICommand
    {
        private readonly Action<T> _executeMethod;
        private readonly Predicate<T> _canExecuteMethodT;

        #region ICommand Members

        public DelegateCommand(Action<T> executeMethod, Predicate<T> canExecuteMethod = null)
        {
            _executeMethod = executeMethod;
            _canExecuteMethodT = canExecuteMethod;
        }

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }

        #endregion

        public bool CanExecute(object parameter)
        {
            throw new NotImplementedException();
        }


        public void Execute(object parameter)
        {
            throw new NotImplementedException();
        }
    }

    public class AutoCanExecuteCommandWrapper : ICommand
    {
        public ICommand WrappedCommand
        {
            get;
            private set;
        }

        public AutoCanExecuteCommandWrapper(ICommand wrappedCommand)
        {
            if (wrappedCommand == null)
            {
                throw new ArgumentNullException("wrappedCommand");
            }

            WrappedCommand = wrappedCommand;
        }

        public void Execute(object parameter)
        {
            WrappedCommand.Execute(parameter);
        }

        public bool CanExecute(object parameter)
        {
            return WrappedCommand.CanExecute(parameter);
        }

        public event EventHandler CanExecuteChanged
        {
            add { CommandManager.RequerySuggested += value; }
            remove { CommandManager.RequerySuggested -= value; }
        }
    }
}
