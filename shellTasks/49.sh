#!/bin/bash

name=$(hostname -s)
user=$(whoami)

[[ $user != "oracle" ]] && [[ $user != "grid" ]] && echo not allowed && exit 1
[[ -z ${ORACLE_BASE} ]] && [[ -z ${ORACLE_HOME} ]] && exit 2

if [[ ! -f $ORACLE_HOME/bin/sqlplus ]] ;then exit 3 fi

if [[ -z $ORACLE_SID ]] ;then exit 4 fi

if [[ ! -x $ORACLE_HOME/bin/sqlplus ]];then exit 5 fi

role=""

if [[ $user == "oracle" ]];then role="SYSDBA"
else rele="SYSASM" fi

diagnostic_des=""
diag_base=""
diag_dir=""
if sqlplus -SL "/ as $role" @a.sql | sed -n  '4p';then
	diagnostic_dest=$(sqlplus -SL "/ as $role" @a.sql | sed -n '4p')

	if [ -z $diagnostic_dest ];then 
		diag_base=$ORACLE_BASE
	else
		diag_base=$diagnostic_des
		if [ ! -f "${diagbase}/diag"  ];then exit 7 fi
		diag_dir="$diag_base/diag"
	fi
	trace=""
	if [ $user == "grid" ];then
	trace="$diag_dir/crs/$name/crs/trace"
	fi
else
	exit 6
fi

