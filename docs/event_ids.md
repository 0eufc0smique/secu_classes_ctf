# Windows Event IDs Reference

This document provides a comprehensive reference for Windows Event IDs commonly used in security monitoring and incident response.

## Authentication & Logon Events

### Successful Logons
- **4624**: User successfully logged on to a computer (includes RDP connections)
- **4648**: User successfully logged on using explicit credentials while already logged on as different user
- **4776**: Domain controller attempted to validate credentials for an account
- **4778**: Session was reconnected to a Window Station

### Failed Logons
- **4625**: Failed logon attempt with unknown username or bad password
- **4771**: Kerberos pre-authentication failed
- **4772**: Kerberos authentication ticket request failed

### Logoff Events
- **4634**: Logoff process completed for user
- **4647**: User initiated logoff
- **4779**: User disconnected terminal server or virtual host session without logging off

### Kerberos Authentication
- **4768**: Kerberos authentication ticket (TGT) was requested
- **4769**: Kerberos service ticket was requested
- **4770**: Kerberos service ticket was renewed
- **4820**: Kerberos Ticket-granting-ticket (TGT) was denied
- **4821**: Kerberos service ticket was denied due to access control restrictions
- **4822**: NTLM authentication failed because account was member of Protected User group
- **4823**: NTLM authentication failed because access control restrictions are required
- **4824**: Kerberos pre-authentication failed because account was member of Protected User group

## Account Management Events

### User Account Operations
- **4720**: User account was created
- **4722**: User account was enabled
- **4723**: Password change attempt was made for an account
- **4724**: Password reset attempt was made for an account
- **4725**: User account was disabled
- **4726**: User account was deleted
- **4738**: User account was modified
- **4740**: User account was locked out

### Group Management
- **4727**: Security-enabled global group was created
- **4730**: Security-enabled global group was deleted
- **4732**: Member was added to security-enabled global group
- **4733**: Member was removed from security-enabled global group
- **4798**: User's local group membership was enumerated
- **4799**: Security-enabled local group membership was enumerated

### SID History
- **4765**: SID History was added to an account
- **4766**: Failed attempt to add SID History to an account

## Privilege Use Events

### Special Privileges
- **4672**: Special privileges assigned to new logon
- **4673**: Privileged service was called
- **4674**: Attempted operation on privileged object
- **4964**: Special groups assigned new logon

### Object Access
- **4656**: Request to handle or access an object
- **4658**: Handle to an object was closed
- **4659**: Handle to an object was requested with intent to delete
- **4660**: Object was deleted
- **4663**: Attempt to access object was made
- **4664**: Attempt to create a hard link was made
- **4670**: Object permissions were changed
- **4691**: Indirect access to an object was requested

## Process & Service Events

### Process Creation/Termination
- **4688**: New process was created
- **4689**: Process was terminated

### Service Management
- **4697**: Service was installed in the system
- **4671**: Application attempted to listen on a port

### Scheduled Tasks
- **4698**: Scheduled task was created
- **4699**: Scheduled task was deleted
- **4700**: Scheduled task was enabled
- **4701**: Scheduled task was disabled
- **4702**: Scheduled task was updated

## PowerShell Events

- **4100**: PowerShell engine state was changed
- **4103**: PowerShell module logging
- **4104**: PowerShell script block logging
- **4105**: PowerShell script started
- **4106**: PowerShell command invocation

## Windows Management Instrumentation (WMI)

- **5857**: WMI provider was loaded
- **5858**: WMI provider was unloaded
- **5860**: WMI method execution
- **5861**: WMI namespace access

## Security Policy Changes

- **4719**: System audit policy was changed
- **4739**: Domain policy was changed
- **4902**: User audit policy table was created
- **4904**: Security policy of Group Policy object was applied
- **4906**: Audit policy modification was attempted
- **4907**: Audit settings on an object were modified

## Audit Log Management

- **1100**: Event logging service has shut down
- **1101**: Audit events have been dropped by the transport
- **1102**: Audit log was cleared
- **1104**: Security log is now full
- **4618**: Monitored security event pattern occurred
- **4649**: Potential replay attack detected
- **4897**: Role separation enabled

## Microsoft Defender Antivirus Events

- **1002**: Malware scan stopped before completing scan
- **1003**: Malware scan paused
- **1005**: Malware scan failed
- **1006, 1116**: Malware or unwanted software detected
- **1007, 1117**: Action to protect system performed
- **1008, 1118**: Action to protect system failed
- **1009**: Item restored from quarantine
- **1012**: Unable to delete item in quarantine
- **1015**: Suspicious behavior detected
- **1119**: Critical error occurred when taking action

## Additional Security Events

### Directory Services
- **4794**: Attempt at setting Directory Services Restore Mode

### OCSP Responder
- **5124**: Update to security setting on OCSP Responder Service

### File System
- **5051**: File was virtualized
- **4985**: Transaction state change

### Remote Desktop Services
- **1149**: Remote Desktop Services

## Event ID Ranges Summary

- **1000-1999**: Microsoft Defender Antivirus events
- **4000-4999**: PowerShell and application events
- **4600-4999**: Security events (logon, account management, privilege use)
- **5000-5999**: File system and application events
- **1100-1199**: System audit events
- **5800-5999**: WMI events

---

*This reference consolidates duplicate Event IDs and provides consistent descriptions for security monitoring purposes.*